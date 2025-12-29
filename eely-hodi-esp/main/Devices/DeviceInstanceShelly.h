// Eely-HoDi - (c) 2022-24 by Joerg Plenert | https://eely.eu
#ifndef DeviceInstanceShelly_h
#define DeviceInstanceShelly_h

using namespace std;

#include "DeviceInstance.h"
#include "ConfigStoreApp.h"
#include "Json.h"

class DeviceInstanceShelly : public DeviceInstance
{
private:
    ConfigDeviceShelly& _config;
    int _deviceGeneration;

public:
    DeviceInstanceShelly(int deviceGeneration, ConfigDeviceShelly& config);
    string GetDeviceId() override;
    string GetDeviceName() override;

protected:
    Json GetStatus();
};

#endif

