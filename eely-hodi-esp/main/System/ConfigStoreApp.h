// Eely-HoDi - (c) 2022-24 by Joerg Plenert | https://eely.eu
#ifndef ConfigStoreGM_h
#define ConfigStoreGM_h

#include <ConfigStore.h>
#include <list>
#include <vector>
#include <optional>
#include "Json.h"

using namespace std;

enum DeviceType
{
    DeviceType_Unknown,
    DeviceType_Shelly_3EM,
    DeviceType_Shelly_HT,
    DeviceType_Shelly_PlugS,
    DeviceType_Shelly_Pro3EM,

    DeviceType_Tibber_Price,
};

enum DeviceAccessType
{
    DeviceAccess_None,
    DeviceAccess_Shelly_Direct,
    DeviceAccess_Shelly_CloudAPI,  
};

enum EnergyDisplayType
{
    EnergyDisplay_None,
    EnergyDisplay_Total,
    EnergyDisplay_Total_p_Production,
    EnergyDisplay_Total_p_Production_p_Storage,
};

class ConfigStoreApp;

class ConfigDeviceBase
{
public:
    DeviceType type;
    DeviceAccessType access;
    string name;
    ConfigStoreApp& base_config_;

    ConfigDeviceBase(ConfigStoreApp& base_config) : type(DeviceType_Unknown), access(DeviceAccess_None), base_config_(base_config){}
};

class ConfigDeviceTibber : public ConfigDeviceBase {
    public:
        ConfigDeviceTibber(ConfigStoreApp& base_config) : ConfigDeviceBase(base_config) {}
};

class ConfigDeviceShelly : public ConfigDeviceBase
{
public:
    string devId;
    string host;
    string username;
    string password;

    ConfigDeviceShelly(ConfigStoreApp& base_config) : ConfigDeviceBase(base_config) {}
};

struct DeviceIndex
{
    int device_index;
    int value_index;
};

struct EnergyEquationItem
{
    bool minus;             // else Plus    
    DeviceIndex device_index;
};

class ClimateInfoItem
{
public:
    string text;
    vector<DeviceIndex> device_index_list;

    bool IsEmpty() { return text.empty(); }
};

class ConfigStoreApp : public ConfigStore
{
    public:
        string _hodiConfigError;
        int _displayBrightness;  // 0-255
        int _clockColor;

        string _shellyAuthKey;
        string _shellyCloudHost;

        string _tibberToken;

        vector<ConfigDeviceBase*> _devices;

        vector<EnergyEquationItem> _energyTotal;
        vector<EnergyEquationItem> _energyConsumption;
        vector<EnergyEquationItem> _energyProduction;
        vector<EnergyEquationItem> _energyStorage;

        EnergyDisplayType _energyDisplayType;

        ClimateInfoItem _climate_1;
        ClimateInfoItem _climate_2;
        ClimateInfoItem _climate_3;

        bool _showStatusSubtitle;
        bool _showRssiSubtitle;
        bool _showEnergyPrice;

    public:
        ConfigStoreApp() : ConfigStore(), _displayBrightness(0), _clockColor(0), _energyDisplayType(EnergyDisplay_None), _showStatusSubtitle(false), _showRssiSubtitle(false), _showEnergyPrice(false) {}
        ConfigStoreApp(const char* fileName) : ConfigStore(fileName), _displayBrightness(0), _clockColor(0), _energyDisplayType(EnergyDisplay_None), _showStatusSubtitle(false), _showRssiSubtitle(false), _showEnergyPrice(false) {}

    protected:
        void ReadValues(Json& json) override;
        void WriteValues(Json& json) override;

        bool ReadHoDiConfig(Json& json);
        ConfigDeviceBase* ReadDevice(Json& json);
        ConfigDeviceShelly* ReadShellyDevice(Json& json);
        ClimateInfoItem ReadClimateInfoItem(char* input, string error_path);
        optional<vector<EnergyEquationItem>> ReadEnergyEquationItem(char* input, string error_path);
        optional<DeviceIndex> ReadDeviceIndex(char* input, int* idx, string error_path);
};

#endif