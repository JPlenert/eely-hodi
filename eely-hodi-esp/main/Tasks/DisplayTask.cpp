// Eely-HoDi - (c) 2022-24 by Joerg Plenert | https://eely.eu
#include "DisplayTask.h"

#include "string_format.h"

#include "ConfigStoreApp.h"
#include "Eelyapp.h"
#include "esp_log.h"
#include "wifi.h"

#include "DisplayLogic.h"
#include "Logic/SubtitleDisplayTextEnergy.h"
#include "Logic/SubtitleDisplayTextClimate.h"
#include "Logic/SubtitleDisplayTextStatus.h"
#include "Logic/SubtitleDisplayTextRssi.h"
#include "Logic/SubtitleDisplayTextEnergyPrice.h"

static const char* TAG = "DisplayTask";

DisplayTask::DisplayTask(ConfigStoreApp& config, vector<DeviceInstance*>& devices) : _config(config), _devices(devices)
{
	_lastTS = 0;

	_imageShowDuration = 0;
	_imageShowTS = 0;
	_imageToShow = nullptr;

	_subtitleShowDuration = 0;
	_subtitleShowTS = 0;

	_defaultSubtitleIndex = 0;
	_defaultSubtitleShowTime = 0;
	
	_wifiErrorCount = 0;
	_deviceErrorCount = 0;
}

void DisplayTask::PreWork()
{
	_taskDelay = 250 / portTICK_PERIOD_MS;

	_imageShowTS = 0;
	_imageToShow = NULL;

	_subtitleShowTS = 0;
	_subtitleToShowCurrent.clear();
	_subtitleToShow.clear();

	// Init the default screens
	if (_config._energyDisplayType != EnergyDisplay_None)
		_defaultSubtitleScreens.push_back(new SubtitleDisplayTextEnergy(_config, _devices));
	if (!_config._climate_1.IsEmpty())
		_defaultSubtitleScreens.push_back(new SubtitleDisplayTextClimate(_config._climate_1, _devices));
	if (_config._showStatusSubtitle)
		_defaultSubtitleScreens.push_back(new SubtitleDisplayTextStatus());
	if (_config._showRssiSubtitle)	
		_defaultSubtitleScreens.push_back(new SubtitleDisplayTextRssi());
	if (_config._showEnergyPrice)	
		_defaultSubtitleScreens.push_back(new SubtitleDisplayTextEnergyPrice(_config, _devices));


	OnSettingsChanged();
}

bool DisplayTask::SetImageToShow(unsigned char* image, int duration)
{
	if (_imageToShow != NULL)
		return false;

	_imageShowDuration = duration;
	_imageToShow = image;

	ESP_LOGI(TAG, "setImageToShow() called");

	return true;
}

bool DisplayTask::SetSubtitleToShow(char* subtitle, int duration)
{
	// Must be processed by the worker before set new subtitle
	if (!_subtitleToShow.empty())
		return false;

	_subtitleShowDuration = duration;
	_subtitleToShow = subtitle;

	ESP_LOGI(TAG, "setSubtitleToShow() called with text %s", subtitle);

	return true;
}


void DisplayTask::Work()
{
	bool redraw = false;

	time_t nowTime;
	time(&nowTime);

	// Display new image
	if (_imageToShow != NULL)
	{
		_imageShowTS = nowTime + _imageShowDuration;

		Display_ShowImage(_imageToShow);
		free(_imageToShow);
		_imageToShow = NULL;

		ESP_LOGI(TAG, "new image set");
		return;
	}
	else if (_imageShowTS != 0)
	{
		if (nowTime > _imageShowTS)
		{
			_imageShowTS = 0;
			ESP_LOGI(TAG, "image show time is over");
		}
		else
			// Keep on showing image
			return;
	}

	// Display new subtitle
	else if (!_subtitleToShow.empty())
	{
		_subtitleShowTS = nowTime + _subtitleShowDuration;
		_subtitleToShowCurrent = _subtitleToShow;
		_subtitleToShow.clear();

		ESP_LOGI(TAG, "new subtitle set");

		redraw = true;
	}
	else if (_subtitleShowTS != 0)
	{
		if (nowTime > _subtitleShowTS)
		{
			_subtitleShowTS = 0;
			_subtitleToShowCurrent.clear();
			ESP_LOGI(TAG, "subtitle show time is over");
			redraw = true;
		}
	}

	// Show current time
	if (nowTime != _lastTS || redraw)
	{
		struct tm* timeinfo;

		if (g_eelyapp->GetSystemStatusString(true).empty())
		{
			_wifiErrorCount = 0;
			_deviceErrorCount = 0;
		}
		else
		{
			if (wifi_status_get() != WifiStatus_StationOK)
			{
				_wifiErrorCount++;
				_deviceErrorCount = 0;
			}
			else
			{
				_deviceErrorCount++;
				_wifiErrorCount = 0;
			}
		}

		timeinfo = localtime(&nowTime);
		Display_DrawTime(timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, _defaultSubtitleScreens.size() == 0, _wifiErrorCount, _deviceErrorCount);
		if (!_subtitleToShowCurrent.empty())
			Display_DrawSubtitle(_subtitleToShowCurrent.c_str());
		else 
		{
			if (_defaultSubtitleScreens.size() > 0)
			{
				string text_to_draw;

				_defaultSubtitleShowTime--;
				if (_defaultSubtitleShowTime > 0)
				{
					// for the unlikely case there is nothing to show index is -1
					if (_defaultSubtitleIndex >= 0)
					{
						text_to_draw = _defaultSubtitleScreens[_defaultSubtitleIndex]->GetText();
					}
				}
				else
				{
					// Find next screen to show
					// Limit tries to find a new index
					int foundIndex = -1;
					for (int i=0; i<=_defaultSubtitleScreens.size(); i++)
					{
						_defaultSubtitleIndex++;
						if (_defaultSubtitleIndex >= _defaultSubtitleScreens.size())
							_defaultSubtitleIndex = 0;

						if (_defaultSubtitleScreens[_defaultSubtitleIndex]->HasText())
						{
							foundIndex = _defaultSubtitleIndex;
							break;
						}
					}

					_defaultSubtitleIndex = foundIndex;
					if (_defaultSubtitleIndex != -1)
					{
						_defaultSubtitleShowTime = _defaultSubtitleScreens[_defaultSubtitleIndex]->DisplayTime();
						text_to_draw = _defaultSubtitleScreens[_defaultSubtitleIndex]->GetText();
					}
					else
					{
						_defaultSubtitleShowTime = 3;
					}
				}

				if (!text_to_draw.empty())
					Display_DrawSubtitle(text_to_draw.c_str(), true);
			}
		}

		//ESP_LOGI(TAG, "[APP] Free memory: %lu bytes", esp_get_free_heap_size());

		Display_CommitDraw();
		
		// Log display changes
		// Display_ScreenshotToLog();

		_lastTS = nowTime;
	}
}

void DisplayTask::OnSettingsChanged()
{
}
