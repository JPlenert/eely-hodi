// Eely-HoDi - (c) 2022-24 by Joerg Plenert | https://eely.eu
#ifndef SubtitleDisplayTextEnergyPrice_h
#define SubtitleDisplayTextEnergyPrice_h

#include "SubtitleDisplayTextBase.h"
#include "ConfigStoreApp.h"
#include "DeviceInstance.h"

class SubtitleDisplayTextEnergyPrice : public SubtitleDisplayTextBase
{
protected:
	ConfigStoreApp& _config;
	vector<DeviceInstance*>& _devices;

public:
	SubtitleDisplayTextEnergyPrice(ConfigStoreApp& config, vector<DeviceInstance*>& devices);
	bool HasText() override;
	string GetText() override;

};

#endif