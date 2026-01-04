// Eely-HoDi - (c) 2022-26 by Joerg Plenert | https://eely.eu
#ifndef DeviceInstanceShellyPro3EM_h
#define DeviceInstanceShellyPro3EM_h

using namespace std;

#include "DeviceInstanceShelly.h"

class DeviceInstanceShellyPro3EM : public DeviceInstanceShelly
{
private:
    double _totalPower;

    double _p1Power;
    double _p1Pf;
    double _p1Voltage;

    double _p2Power;
    double _p2Pf;
    double _p2Voltage;

    double _p3Power;
    double _p3Pf;
    double _p3Voltage;
public:
    DeviceInstanceShellyPro3EM(ConfigDeviceShelly& config);

    bool DoSync() override;
    double GetLastReadingDouble(int idx) override;
    int GetLastReadingInt(int idx) override;
};

#endif

