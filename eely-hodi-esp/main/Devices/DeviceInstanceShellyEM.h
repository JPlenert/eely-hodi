// Eely-HoDi - (c) 2022-24 by Joerg Plenert | https://eely.eu
#ifndef DeviceInstanceShellyEM_h
#define DeviceInstanceShellyEM_h

using namespace std;

#include "DeviceInstanceShelly.h"

class DeviceInstanceShellyEM : public DeviceInstanceShelly
{
private:
    double _totalPower;

    double _p1Power;
    double _p1Voltage;

    double _p2Power;
    double _p2Voltage;

public:
    DeviceInstanceShellyEM(ConfigDeviceShelly& config);

    bool DoSync() override;
    double GetLastReadingDouble(int idx) override;
    int GetLastReadingInt(int idx) override;
};

#endif

