// Eely-HoDi - (c) 2022-26 by Joerg Plenert | https://eely.eu
#include "DeviceInfoGetHodiHandler.h"
#include "Eelyapp.h"
#include "DeviceTask.h"
#include "esp_wifi.h"

void DeviceInfoGetHodiHandler :: CollectInfo(Json &reply)
{
    int rssi = 0;

    DeviceInfoGetHandler::CollectInfo(reply);
    esp_wifi_sta_get_rssi(&rssi);
    reply.SetInt("rssi", rssi);

    JsonArray devArray = reply.AddArray("devices");
    DeviceTask* dt = (DeviceTask*)g_eelyapp->GetFeature(g_eelyapp->FEATKEY_DEVICETASK);

    for (auto device = dt->_devicesVector.begin(); device != dt->_devicesVector.end(); device++)
    {
        Json newNode = devArray.AddNode();
        newNode.SetString("device_id", (*device)->GetDeviceId());
        newNode.SetString("device_name", (*device)->GetDeviceName());
        newNode.SetString("device_last_error", (*device)->_lastError);
    }
}
