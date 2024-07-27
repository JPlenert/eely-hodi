// Eely-HoDi - (c) 2022-24 by Joerg Plenert | https://eely.eu
#include "HttpClient.h"
#include "DeviceInstanceTibberPrice.h"
#include "string_format.h"
#include "esp_log.h"

static const char* TAG = "DeviceInstanceTibberPrice";

#define DIRECT_BUFFER_SIZE (7*1024)

DeviceInstanceTibberPrice :: DeviceInstanceTibberPrice(ConfigDeviceTibber& config) : DeviceInstance(14400, config), _config(config)
{
	memset(_prices, 0, sizeof(double)*48);
	memset(_priceRatings, 0, sizeof(char)*48);
}

string DeviceInstanceTibberPrice::GetDeviceId()
{
	return "tibber";
}

string DeviceInstanceTibberPrice::GetDeviceName()
{
	return _config.name;
}

Json DeviceInstanceTibberPrice::GetStatus()
{
	char* buffer = (char*)malloc(DIRECT_BUFFER_SIZE);
	Json json;
	int res=0;
	HttpClient http;

	http.SetUrl("https://api.tibber.com/v1-beta/gql");
	http.AddRequestHeader("Content-Type", "application/json");
	string bearer = string_format("Bearer %s", _config.base_config_._tibberToken.c_str());
	http.AddRequestHeader("Authorization", bearer.c_str());
	const char* request= "{ \"query\": \"{viewer{homes{currentSubscription{priceInfo{today{total level}tomorrow{total level}}}}}}\" }";
	res = http.Post(request, buffer, DIRECT_BUFFER_SIZE);

	if (res > 0)
	{
		json = Json(buffer);
		free(buffer);

		optional<Json> jNode = json.GetNode("data");
		if (!jNode.has_value())
		{
			_lastError = "no data in answer";
			_continuousSyncErrorCount++;
			return {};
		}

		jNode = jNode.value().GetNode("viewer");
		if (!jNode.has_value())
		{
			_lastError = "no viewers in answer";
			_continuousSyncErrorCount++;
			return {};
		}

		optional<JsonArray> jArray = jNode.value().GetArray("homes");
		if (!jArray.has_value())
		{
			_lastError = "no homes in answer";
			_continuousSyncErrorCount++;
			return {};
		}

		jNode = jArray.value().GetFirst().value().GetNode("currentSubscription");
		if (!jNode.has_value())
		{
			_lastError = "no currentSubscription in answer";
			_continuousSyncErrorCount++;
			return {};
		}

		jNode = jNode.value().GetNode("priceInfo");
		if (!jNode.has_value())
		{
			_lastError = "no priceInfo in answer";
			_continuousSyncErrorCount++;
			return {};
		}

		_lastError = "";
		_continuousSyncErrorCount = 0;
		return jNode.value();
	}
	else
	{
		_lastError = "http:" + http.GetLastError();
		ESP_LOGI(TAG, "Error getting data: %s", _lastError.c_str());
		_continuousSyncErrorCount++;
	}

	free(buffer);

	return json;
}

bool DeviceInstanceTibberPrice::DoSync()
{
	Json status = GetStatus();
	optional<JsonArray> pricesArray;
	optional<Json> jNode;

	if (status.IsEmpty())
	{
		// _lastError was set bet GetStatus
		return false;
	}

	pricesArray = status.GetArray("today");	
	if (!pricesArray.has_value())
	{
		_lastError = "no today in answer";
		return false;
	}

	// ToDo: Will not work for Days with daylight saving time change
	// Maybe check if we have <> 24 values?
	jNode = pricesArray.value().GetFirst();
	for (int i= 0; i<min(pricesArray.value().GetSize(), 24); i++)
	{
		_prices[i] = jNode.value().GetDouble("total");
		_priceRatings[i] = GetPriceRatingFromLevel(jNode.value().GetCString("level"));
		jNode = pricesArray.value().GetNext();
	}

	pricesArray = status.GetArray("tomorrow");	
	// Tomorrow prices are available starting at 13:00
	if (pricesArray.has_value())
	{
		jNode = pricesArray.value().GetFirst();
		if (jNode.has_value())
		{
			for (int i= 0; i< min(pricesArray.value().GetSize(), 24); i++)
			{
				_prices[24+i] = jNode.value().GetDouble("total");
				_priceRatings[24+i] = GetPriceRatingFromLevel(jNode.value().GetCString("level"));
				jNode = pricesArray.value().GetNext();
			}
		}
	}

	_lastError = "";

	return true;
}

uint8_t DeviceInstanceTibberPrice :: GetPriceRatingFromLevel(char* priceLevel)
{
	if (strcmp(priceLevel, "CHEAP") == 0)
		return 0;
	if (strcmp(priceLevel, "VERY_CHEAP") == 0)
		return 1;
	if (strcmp(priceLevel, "NORMAL") == 0)
		return 2;
	if (strcmp(priceLevel, "EXPENSIVE") == 0)
		return 3;
	if (strcmp(priceLevel, "VERY_EXPENSIVE") == 0)
		return 4;
	
	ESP_LOGE(TAG, "Unable to decode price level %s", priceLevel);
	return 2;
}

int DeviceInstanceTibberPrice :: CalcCurValIdx()
{
	time_t nowTime;
	time(&nowTime);

	// ToDo: Daylight saving time ....

	struct tm* timeinfo = localtime(&nowTime);
	int nowDay = timeinfo->tm_mday;
	int valIdx = timeinfo->tm_hour;

	timeinfo = localtime(&_lastSyncTs);
	int syncDay = timeinfo->tm_mday;

	// In case we have tomorrow, but values still start at yesterday
	if (nowDay != syncDay)
		return valIdx + 24;

	return valIdx;
}

double DeviceInstanceTibberPrice::GetLastReadingDouble(int idx)
{
	if (idx >= 0 && idx < 10)	
		return _prices[CalcCurValIdx() + idx];

	return 0;
}

int DeviceInstanceTibberPrice::GetLastReadingInt(int idx)
{
	if (idx >= 0 && idx < 10)	
	{
		int valStartIdx = CalcCurValIdx();

		return (int)_priceRatings[valStartIdx+idx];
	}

	return 0;
}