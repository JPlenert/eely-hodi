// Eely-HoDi - (c) 2022-26 by Joerg Plenert | https://eely.eu
#ifndef SubtitleDisplayTextEnergy_h
#define SubtitleDisplayTextEnergy_h

#include "SubtitleDisplayTextBase.h"
#include "ConfigStoreApp.h"
#include "DeviceInstance.h"

class SubtitleDisplayTextEnergy : public SubtitleDisplayTextBase
{
protected:
	ConfigStoreApp& _config;
	vector<DeviceInstance*>& _devices;
public:
	SubtitleDisplayTextEnergy(ConfigStoreApp& config, vector<DeviceInstance*>& devices);
	bool HasText() override;
	string GetText() override;

protected:
	string GetEnergyDisplay();
	double CalcEnergy(vector<EnergyEquationItem>& en_list);
	string FormatPower(double watt, bool include_unit);
};

#endif