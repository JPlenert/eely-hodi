// Eely-HoDi - (c) 2022-24 by Joerg Plenert | https://eely.eu
#ifndef SubtitleDisplayTextClimate_h
#define SubtitleDisplayTextClimate_h

#include "SubtitleDisplayTextBase.h"
#include "ConfigStoreApp.h"
#include "DeviceInstance.h"

class SubtitleDisplayTextClimate : public SubtitleDisplayTextBase
{
protected:
	ClimateInfoItem _infoItem;
	vector<DeviceInstance*>& _devices;

public:
	SubtitleDisplayTextClimate(ClimateInfoItem infoItem, vector<DeviceInstance*>& devices);
	bool HasText() override;
	string GetText() override;
};

#endif