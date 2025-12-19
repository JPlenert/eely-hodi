// Eely-HoDi - (c) 2022-25 by Joerg Plenert | https://eely.eu
#ifndef DeviceInstanceShellyProEM_h
#define DeviceInstanceShellyProEM_h

using namespace std;

#include "DeviceInstanceShelly.h"

class DeviceInstanceShellyProEM : public DeviceInstanceShelly
{
private:
    double _totalPower;

    double _p1Power;
    double _p1Pf;
    double _p1Voltage;

    double _p2Power;
    double _p2Pf;
    double _p2Voltage;
public:
    DeviceInstanceShellyProEM(ConfigDeviceShelly& config);

    bool DoSync() override;
    double GetLastReadingDouble(int idx) override;
    int GetLastReadingInt(int idx) override;
};

#endif

