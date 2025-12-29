// Eely-HoDi - (c) 2022-24 by Joerg Plenert | https://eely.eu
#ifndef DeviceInstanceShellyHT_h
#define DeviceInstanceShellyHT_h

using namespace std;

#include "DeviceInstanceShelly.h"

class DeviceInstanceShellyHT : public DeviceInstanceShelly
{
private:
    double _lastTempReading;
    double _lastHumReading;

public:
    DeviceInstanceShellyHT(ConfigDeviceShelly& config) : DeviceInstanceShelly(1, config), _lastTempReading(0), _lastHumReading(0) {}
    bool DoSync() override;

    double GetLastReadingDouble(int idx) override;
    int GetLastReadingInt(int idx) override;
};

#endif

