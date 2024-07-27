// Eely-HoDi - (c) 2022-24 by Joerg Plenert | https://eely.eu
#include "Eelyapp.h"
#include "DeviceTask.h"
#include "DeviceInstanceShelly3EM.h"
#include "DeviceInstanceShellyPro3EM.h"
#include "DeviceInstanceShellyHT.h"
#include "DeviceInstanceShellyPlugS.h"
#include "DeviceInstanceTibberPrice.h"
#include "time.h"
#include "esp_log.h"
#include "wifi.h"

static const char* TAG = "DeviceTask";

DeviceTask::DeviceTask(ConfigStoreApp& config) : TaskBase("DeviceTask", 10*1024), _curSyncItemIdx(0)
{
	ApplyConfig(config);
	_taskDelay = 1000 / portTICK_PERIOD_MS;
}

void DeviceTask::ApplyConfig(ConfigStoreApp& config)
{
	for (auto cfg = config._devices.begin(); cfg != config._devices.end(); cfg++)
	{
		if ((*cfg)->type == DeviceType_Shelly_3EM)
		{
			DeviceInstanceShelly3EM *dev = new DeviceInstanceShelly3EM((ConfigDeviceShelly&)**cfg);
			_devicesVector.push_back(dev);
			_devicesPrioList.push_back(dev);
		}
		else if ((*cfg)->type == DeviceType_Shelly_Pro3EM)
		{
			DeviceInstanceShellyPro3EM *dev = new DeviceInstanceShellyPro3EM((ConfigDeviceShelly&)**cfg);
			_devicesVector.push_back(dev);
			_devicesPrioList.push_back(dev);
		}
		else if ((*cfg)->type == DeviceType_Shelly_HT)
		{
			DeviceInstanceShellyHT* dev = new DeviceInstanceShellyHT((ConfigDeviceShelly&)**cfg);
			_devicesVector.push_back(dev);
			_devicesPrioList.push_back(dev);
		}		
		else if ((*cfg)->type == DeviceType_Shelly_PlugS)
		{
			DeviceInstanceShellyPlugS* dev = new DeviceInstanceShellyPlugS((ConfigDeviceShelly&)**cfg);
			_devicesVector.push_back(dev);
			_devicesPrioList.push_back(dev);
		}
		else if ((*cfg)->type == DeviceType_Tibber_Price)
		{
			DeviceInstanceTibberPrice* dev = new DeviceInstanceTibberPrice((ConfigDeviceTibber&)**cfg);
			_devicesVector.push_back(dev);
			_devicesPrioList.push_back(dev);
		}
	}
}

void DeviceTask::Work()
{	
	time_t now;
	time(&now);

	// Stop accessing devices if wifi is not accessible
	// This may help to recover from wifi connection losts more quickly
	if (wifi_status_get() != WifiStatus_StationOK)
		return;

	for (list<DeviceInstance*>::iterator item = _devicesPrioList.begin(); item != _devicesPrioList.end();)
	{
		DeviceInstance* curItem = *item;

		// Find item to be processed
		if (now >= curItem->_lastSyncTs + curItem->_syncFrequencyS)
		{
			// Sync and push item to the back. This ensures we process the unprocessed next.
			ESP_LOGI(TAG, "Syncing %s", curItem->GetDeviceId().c_str());
			if (curItem->DoSync())
				curItem->_lastSyncTs = now;
			_devicesPrioList.remove(curItem);
			_devicesPrioList.push_back(curItem);
			break;			
		}

		item++;
	}

	// Walk though all device instances and check if have can not access a device
	bool errored_device = false;
	for (auto dev = _devicesVector.begin(); dev != _devicesVector.end(); dev++)
	{
		if ((*dev)->_continuousSyncErrorCount >= 3)
		{
			errored_device = true;
			break;
		}
	}

	g_eelyapp->setDeviceError(errored_device);
}