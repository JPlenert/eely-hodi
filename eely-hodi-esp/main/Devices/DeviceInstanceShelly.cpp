// Eely-HoDi - (c) 2022-24 by Joerg Plenert | https://eely.eu
#include "HttpClient.h"
#include "DeviceInstanceShelly.h"
#include "string_format.h"
#include "esp_log.h"

static const char* TAG = "DeviceInstanceShelly";

#define DIRECT_BUFFER_SIZE (2*1024)

DeviceInstanceShelly :: DeviceInstanceShelly(ConfigDeviceShelly& config) : DeviceInstance(0, config), _config(config)
{
	if (_config.access == DeviceAccess_Shelly_Direct)
		_syncFrequencyS = 20;
	else if (_config.access == DeviceAccess_Shelly_CloudAPI)
		_syncFrequencyS = 60;
}

string DeviceInstanceShelly::GetDeviceId()
{
	return _config.devId;
}

string DeviceInstanceShelly::GetDeviceName()
{
	return _config.name;
}

Json DeviceInstanceShelly::GetStatus()
{
	char* buffer = (char*)malloc(DIRECT_BUFFER_SIZE);
	Json json;
	int res=0;
	HttpClient http;

	if (_config.access == DeviceAccess_Shelly_Direct)
	{
		if (_config.type == DeviceType_Shelly_PlugS || _config.type == DeviceType_Shelly_Pro3EM || _config.type == DeviceType_Shelly_ProEM)
		{
			// Gen2 Devices with enabled auth are using the digest algorithm for authentication
			// This was introduced on Dec 15, 2023 and is not part of V5.1.2 of ESP IDF
			// So currently we use local modifications
			ESP_LOGI(TAG, "Type DeviceAccess_Shelly_Direct (Gen2)");
			http.SetUrl(string_format("http://%s/rpc/Shelly.GetStatus", _config.host.c_str()));
			if (!_config.username.empty())
				http.SetDigestAuth(_config.username, _config.password);
		}
		else
		{
			ESP_LOGI(TAG, "Type DeviceAccess_Shelly_Direct (Gen1)");
			http.SetUrl(string_format("http://%s/status", _config.host.c_str()));
			if (!_config.username.empty())
				http.SetBasicAuth(_config.username, _config.password);
		}

		res = http.Get(buffer, DIRECT_BUFFER_SIZE);

		if (res > 0)
		{
			json = Json(buffer);
			if (json.IsEmpty())
			{
				_continuousSyncErrorCount++;
				_lastError = "Status is empty";
			}
			else
				_continuousSyncErrorCount = 0;
		}
		else
		{
			_lastError = http.GetLastError();
			if (_lastError.empty())
				_lastError = "http GET failed";
			ESP_LOGI(TAG, "Error getting data: %s", _lastError.c_str());
			_continuousSyncErrorCount++;
		}
	}
	else if (_config.access == DeviceAccess_Shelly_CloudAPI)
	{
		ESP_LOGI(TAG, "Type DeviceAccess_Shelly_CloudAPI");
		http.SetUrl(string_format("https://%s/device/status", _config.base_config_._shellyCloudHost.c_str()));
		http.AddRequestHeader("Content-Type", "application/x-www-form-urlencoded");
		string form_data = string_format("id=%s&auth_key=%s", _config.devId.c_str(), _config.base_config_._shellyAuthKey.c_str());
		res = http.Post(form_data.c_str(), buffer, DIRECT_BUFFER_SIZE);

		if (res > 0)
		{
			json = Json(buffer);
			free(buffer);

			if (!json.GetBool("isok"))
			{
				_lastError = "isok is false";
				_continuousSyncErrorCount++;
				return {};
			}
			optional<Json> jNode = json.GetNode("data");
			if (!jNode.has_value())
			{
				_lastError = "no data in answer";
				_continuousSyncErrorCount++;
				return {};
			}
			jNode = jNode.value().GetNode("device_status");
			if (!jNode.has_value())
			{
				_lastError = "no device_status in answer";
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
	}

	free(buffer);

	return json;
}