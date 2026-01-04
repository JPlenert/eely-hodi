// Eely-HoDi - (c) 2022-26 by Joerg Plenert | https://eely.eu
#ifndef DeviceInstanceShellyPlugS_h
#define DeviceInstanceShellyPlugS_h

using namespace std;

#include "DeviceInstanceShelly.h"

class DeviceInstanceShellyPlugS : public DeviceInstanceShelly
{
private:
    double _power;
    double _voltage;
public:
    DeviceInstanceShellyPlugS(ConfigDeviceShelly& config);

    bool DoSync() override;
    double GetLastReadingDouble(int idx) override;
    int GetLastReadingInt(int idx) override;
};

#endif

