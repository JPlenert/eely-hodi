// Eely-HoDi - (c) 2022-24 by Joerg Plenert | https://eely.eu
#ifndef DeviceInstanceShellyEMGen1_h
#define DeviceInstanceShellyEMGen1_h

using namespace std;

#include "DeviceInstanceShelly.h"

class DeviceInstanceShellyEMGen1 : public DeviceInstanceShelly
{
private:
    double _totalPower;

    double _p1Power;
    double _p1Voltage;

    double _p2Power;
    double _p2Voltage;

public:
    DeviceInstanceShellyEMGen1(ConfigDeviceShelly& config);

    bool DoSync() override;
    double GetLastReadingDouble(int idx) override;
    int GetLastReadingInt(int idx) override;
};

#endif

