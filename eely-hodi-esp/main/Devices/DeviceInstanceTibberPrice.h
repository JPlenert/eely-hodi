// Eely-HoDi - (c) 2022-24 by Joerg Plenert | https://eely.eu
#ifndef DeviceInstanceTibberPrice_h
#define DeviceInstanceTibberPrice_h

using namespace std;

#include "DeviceInstance.h"
#include "ConfigStoreApp.h"
#include "Json.h"

class DeviceInstanceTibberPrice : public DeviceInstance
{
private:
    ConfigDeviceTibber& _config;

    double _prices[48];
    uint8_t _priceRatings[48]; // 0-4 - Very_Cheap to Very_High

public:
    DeviceInstanceTibberPrice(ConfigDeviceTibber& config);
    string GetDeviceId() override;
    string GetDeviceName() override;

    bool DoSync() override;
    double GetLastReadingDouble(int idx) override;
    int GetLastReadingInt(int idx) override;

protected:
    Json GetStatus();
    
private:
	int CalcCurValIdx();
    uint8_t GetPriceRatingFromLevel(char* priceLevel);
};

#endif