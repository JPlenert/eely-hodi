// Eely-HoDi - (c) 2022-25 by Joerg Plenert | https://eely.eu
#ifndef DeviceInstanceShellyEMGen3_h
#define DeviceInstanceShellyEMGen3_h

using namespace std;

#include "DeviceInstanceShelly.h"

class DeviceInstanceShellyEMGen3 : public DeviceInstanceShelly
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
    DeviceInstanceShellyEMGen3(ConfigDeviceShelly& config);

    bool DoSync() override;
    double GetLastReadingDouble(int idx) override;
    int GetLastReadingInt(int idx) override;
};

#endif

