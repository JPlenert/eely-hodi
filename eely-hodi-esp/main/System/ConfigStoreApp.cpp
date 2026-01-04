// Eely-HoDi - (c) 2022-26 by Joerg Plenert | https://eely.eu
#include "ConfigStoreApp.h"
#include "esp_log.h"
#include <algorithm>
#include <string.h>

static const char *TAG = "ConfigStoreApp";


void ConfigStoreApp :: ReadValues(Json& json)
{
    ConfigStore::ReadValues(json);

    optional<Json> hodi = json.GetNode("hodi");
    
    if (hodi.has_value())
    {
        ESP_LOGI(TAG, "rading hodi config");
        ReadHoDiConfig(hodi.value());
        ESP_LOGI(TAG, "Shelly device count %d", _devices.size());
    }
    else
    {
        ESP_LOGW(TAG, "not hodi config available");
    }

    if (!_hodiConfigError.empty())
        ESP_LOGE(TAG, "Error processing log: %s", _hodiConfigError.c_str());

    _hodiConfigError = "";
}

bool ConfigStoreApp :: ReadHoDiConfig(Json& json)
{
    optional<Json> optChapter;

    optChapter = json.GetNode("display");
    if (optChapter.has_value())
    {
        ESP_LOGI(TAG, "Has display");
        _displayBrightness = optChapter.value().GetInt("brightness");
        _clockColor = optChapter.value().GetInt("clock_color");
        _showStatusSubtitle = optChapter.value().GetBool("show_status_subtitle");
        _showRssiSubtitle = optChapter.value().GetBool("show_rssi_subtitle");
        _showEnergyPrice = optChapter.value().GetBool("show_energy_price");
    }
    else
    {
        ESP_LOGI(TAG, "Has no display");
        _displayBrightness = 100;
        _clockColor = 16711680; // Red!
        _showStatusSubtitle = false;
        _showRssiSubtitle = false;
    }
    
    optChapter = json.GetNode("shelly");
    if (optChapter.has_value())
    {
        _shellyAuthKey = (*optChapter).GetString("authkey");
        _shellyCloudHost = (*optChapter).GetString("cloudhost");
    }
    else        
        ESP_LOGI(TAG, "Has no shelly");

    optChapter = json.GetNode("tibber");
    if (optChapter.has_value())
    {
        _tibberToken = (*optChapter).GetString("token");
    }
    else        
        ESP_LOGI(TAG, "Has no tibber");
    

    optional<JsonArray> deviceArray = json.GetArray("devices");
    if (deviceArray)
    {
        optional<Json> arrayItem = deviceArray.value().GetFirst();
        while (arrayItem)
        {
            // ToDo: enhance to not only shelly devices
            ConfigDeviceBase* device = ReadDevice(*arrayItem);
            if (device == nullptr)
                return false;
            
            _devices.push_back(device);

            arrayItem = (*deviceArray).GetNext();
        }
    }
    else        
        ESP_LOGI(TAG, "Has no devices");

    optChapter = json.GetNode("energy");
    if (optChapter.has_value())
    {
        char* enStr;

        _energyDisplayType = (EnergyDisplayType)optChapter.value().GetInt("displayType");

        enStr = optChapter.value().GetCString("total");
        if (enStr != nullptr)
        {
            auto en_eq = ReadEnergyEquationItem(enStr, "energy>total");
            if (en_eq.has_value())
                _energyTotal = en_eq.value();
            else
                return false;
        }

        enStr = optChapter.value().GetCString("consumption");
        if (enStr != nullptr)
        {
            auto en_eq = ReadEnergyEquationItem(enStr, "energy>consumption");
            if (en_eq.has_value())
                _energyConsumption = en_eq.value();
            else
                return false;
        }

        enStr = optChapter.value().GetCString("production");
        if (enStr != nullptr)
        {
            auto en_eq = ReadEnergyEquationItem(enStr, "energy>production");
            if (en_eq.has_value())
                _energyProduction = en_eq.value();
            else
                return false;
        }

        enStr = optChapter.value().GetCString("storage");
        if (enStr != nullptr)
        {
            auto en_eq = ReadEnergyEquationItem(enStr, "energy>storage");
            if (en_eq.has_value())
                _energyStorage = en_eq.value();
            else
                return false;
        }
    }
    else
    {
        _energyDisplayType = EnergyDisplay_None;
        ESP_LOGI(TAG, "Has no energy");
    }

    char* climate_str = json.GetCString("climate_1");
    if (climate_str != nullptr)
        _climate_1 = ReadClimateInfoItem(climate_str, "climate_1");

    climate_str = json.GetCString("climate_2");
    if (climate_str != nullptr)
        _climate_2 = ReadClimateInfoItem(climate_str, "climate_2");

    climate_str = json.GetCString("climate_3");
    if (climate_str != nullptr)
        _climate_3 = ReadClimateInfoItem(climate_str, "climate_3");

    return true;
}

optional<DeviceIndex> ConfigStoreApp::ReadDeviceIndex(char* input, int* idx, string error_path)
{
    DeviceIndex devIdx = { 0, 0 };
    bool startedValueIndex = false;

    for (; *idx < strlen(input); (*idx)++)
    {
        char curCh = input[*idx];

        if (curCh == '.')
        {
            if (devIdx.device_index == 0)
            {
                _hodiConfigError = error_path + ">early value index";
                return {};
            }
            startedValueIndex = true;
        }
        else if (curCh >= '0' && curCh <= '9')
        {
            if (!startedValueIndex)
            {
                if (devIdx.device_index != 0)
                    devIdx.device_index *= 10;
                devIdx.device_index += (int)(curCh - '0');
            }
            else
            {
                if (devIdx.value_index != 0)
                    devIdx.value_index *= 10;
                devIdx.value_index += (int)(curCh - '0');
            }
        }
        else
            break;
    }

    if (devIdx.device_index == 0)
    {
        _hodiConfigError = error_path + ">no device index";
        return {};
    }
    if (devIdx.device_index > _devices.size())
    {
        _hodiConfigError = error_path + ">device index out of range";
        return {};
    }
    // ToDo: Check value_index (_devices[devIdx.device_index].CheckValueIndex??)

    return optional(devIdx);
}

ClimateInfoItem ConfigStoreApp::ReadClimateInfoItem(char* input, string error_path)
{
    ClimateInfoItem ci;

    for (int idx = 0; idx < strlen(input);)
    {
        if (input[idx] == '$')
        {
            idx++;

            optional<DeviceIndex> devIdx = ReadDeviceIndex(input, &idx, error_path);
            if (devIdx.has_value())
            {
                ci.text += "$";
                ci.device_index_list.push_back(devIdx.value());
            }
            else
            {
                ci.text += "?";
            }

            if (idx < strlen(input) && input[idx] == '*')
            {
                ci.text += "\xb0"; // degree sign
                ci.text += "C";
                idx++;
            }
        }
        else
        {
            ci.text += input[idx];
            idx++;
        }
    }

    return ci;
}

optional<vector<EnergyEquationItem>> ConfigStoreApp::ReadEnergyEquationItem(char* input, string error_path)
{
    vector<EnergyEquationItem> eqi_list;
    EnergyEquationItem cur_eqi;

    for (int idx = 0; idx < strlen(input);)
    {
        if (input[idx] == '+' || input[idx] == '-')
        {
            cur_eqi = EnergyEquationItem();
            cur_eqi.minus = input[idx] == '-';

            idx++;

            optional<DeviceIndex> devIdx = ReadDeviceIndex(input, &idx, error_path);
            if (devIdx.has_value())
            {
                cur_eqi.device_index = devIdx.value();
                eqi_list.push_back(cur_eqi);
            }
            else
                return {};
        }
        else
        {
            _hodiConfigError = error_path + ">invalid char";
            return {};
        }
    }

    return eqi_list;
}

ConfigDeviceBase* ConfigStoreApp :: ReadDevice(Json& json)
{
    string value = json.GetString("type");
    if (value.rfind("shelly_", 0) == 0)
    //if (value == "shelly_3em" || value == "shelly_pro3em" || value == "shelly_ht" || value == "shelly_plugs")
        return ReadShellyDevice(json);
    else if (value == "tibber_price") {
        ConfigDeviceTibber* device = new ConfigDeviceTibber(*this);
        device->type = DeviceType_Tibber_Price;
        device->name = json.GetString("name");

        return device;
    }
    else
    {
        _hodiConfigError = "device>type";
        return {};
    }
}

ConfigDeviceShelly* ConfigStoreApp :: ReadShellyDevice(Json& json)
{
    ConfigDeviceShelly* device = new ConfigDeviceShelly(*this);

    string value = json.GetString("type");
    if (value == "shelly_3em")
        device->type = DeviceType_Shelly_3EM;
    else if (value == "shelly_pro3em")
        device->type = DeviceType_Shelly_Pro3EM;
    else if (value == "shelly_ht")
        device->type = DeviceType_Shelly_HT;
    else if (value == "shelly_plugs")
        device->type = DeviceType_Shelly_PlugS;
    else if (value == "shelly_em_gen1")
        device->type = DeviceType_Shelly_EMGen1;
    else if (value == "shelly_em_gen3")
        device->type = DeviceType_Shelly_EMGen3;
    else if (value == "shelly_proem")
        device->type = DeviceType_Shelly_ProEM;
    else
    {
        _hodiConfigError = "device>type";
        delete device;
        return nullptr;
    }

    value = json.GetString("access");
    if (value == "direct")
        device->access = DeviceAccess_Shelly_Direct;
    else if (value == "cloudAPI")
        device->access = DeviceAccess_Shelly_CloudAPI;
    else
    {
        _hodiConfigError = "devices>access";
        delete device;
        return nullptr;
    }

    device->devId = json.GetString("id");
    if (device->access == DeviceAccess_Shelly_CloudAPI && device->devId.empty())
    {
        _hodiConfigError = "devices>Id";
        delete device;
        return nullptr;
    }

    device->name = json.GetString("name");
    if (device->name.empty())
    {
        _hodiConfigError = "devices>name";
        delete device;
        return nullptr;
    }

    device->host = json.GetString("host");
    if (device->host.empty() && device->access == DeviceAccess_Shelly_Direct)
    {
        _hodiConfigError = "devices>host";
        delete device;
        return nullptr;
    }

    device->username = json.GetString("username");
    device->password = json.GetString("password");

    return device;
}

void ConfigStoreApp :: WriteValues(Json& json)
{
    ConfigStore::WriteValues(json);
    json.SetInt("display_brightness", _displayBrightness);
}