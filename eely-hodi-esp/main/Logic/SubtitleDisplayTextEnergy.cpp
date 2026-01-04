// Eely-HoDi - (c) 2022-26 by Joerg Plenert | https://eely.eu
#include "SubtitleDisplayTextEnergy.h"
#include "string_format.h"
#include "DisplayLogic.h"

SubtitleDisplayTextEnergy :: SubtitleDisplayTextEnergy(ConfigStoreApp& config, vector<DeviceInstance*>& devices) : _config(config), _devices(devices)
{}

bool SubtitleDisplayTextEnergy::HasText()
{
	return true;
}

string SubtitleDisplayTextEnergy::GetText()
{
	return GetEnergyDisplay();
}

string SubtitleDisplayTextEnergy::FormatPower(double watt, bool include_unit)
{
	string fs;

	if (include_unit)
	{
		if (watt >= 10000)
			return string_format("%.0fkW", watt / 1000);
		else if (watt >= 1000)
			return string_format("%.1fkW", watt / 1000);
		else
			return string_format("%.0fW", watt);
	}
	else
	{
		if (watt >= 10000)
			return string_format("%.0f", watt / 1000);
		else if (watt >= 1000)
			return string_format("%.1f", watt / 1000);
		else
			return string_format("%.0f", watt);
	}
}

string SubtitleDisplayTextEnergy::GetEnergyDisplay()
{
	string energyDisplay;

	if (_config._energyDisplayType == EnergyDisplay_None)
		return {};

	if (_config._energyDisplayType == EnergyDisplay_Total ||
		_config._energyDisplayType == EnergyDisplay_Total_p_Production ||
		_config._energyDisplayType == EnergyDisplay_Total_p_Production_p_Storage)
	{
		double value = CalcEnergy(_config._energyTotal);

		if (value > 0)
		{
			energyDisplay = DISPLAY_LOGIC_ESC_GREEN;
		}
		else
		{
			energyDisplay = DISPLAY_LOGIC_ESC_RED;
			value *= -1;
		}

		energyDisplay += FormatPower(value, true);
	}

	if (_config._energyDisplayType == EnergyDisplay_Total_p_Production)
	{
		double value = CalcEnergy(_config._energyProduction);

		if (value >= 0)
		{
			energyDisplay += DISPLAY_LOGIC_ESC_MSPACE;
			energyDisplay += DISPLAY_LOGIC_ESC_YELLOW;
			energyDisplay += "*";
			energyDisplay += FormatPower(value, true);
		}
	}

	if (_config._energyDisplayType == EnergyDisplay_Total_p_Production_p_Storage)
	{
		double value = CalcEnergy(_config._energyStorage);
		if (value >= 0)
		{
			energyDisplay += DISPLAY_LOGIC_ESC_MSPACE;
			energyDisplay += DISPLAY_LOGIC_ESC_BLUE;

			if (value > 0)
			{
				energyDisplay += "L";
			}
			else
			{
				energyDisplay += "E";
				value *= -1;
			}

			energyDisplay += FormatPower(value, true);
		}
	}

	return energyDisplay;
}

double SubtitleDisplayTextEnergy::CalcEnergy(vector<EnergyEquationItem>& en_list)
{
	double value = 0;

	for (auto item = en_list.begin(); item != en_list.end(); item++)
	{
		DeviceInstance* device = _devices[item->device_index.device_index - 1];
		value += (device->GetLastReadingDouble(item->device_index.value_index) * (item->minus ? -1.0 : 1.0));
	}

	return value;
}
