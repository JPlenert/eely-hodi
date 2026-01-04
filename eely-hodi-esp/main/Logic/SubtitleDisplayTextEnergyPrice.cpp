// Eely-HoDi - (c) 2022-26 by Joerg Plenert | https://eely.eu
#include "SubtitleDisplayTextEnergyPrice.h"
#include "string_format.h"
#include "DisplayLogic.h"
#include <cmath>

SubtitleDisplayTextEnergyPrice :: SubtitleDisplayTextEnergyPrice(ConfigStoreApp& config, vector<DeviceInstance*>& devices) : _config(config), _devices(devices)
{}

bool SubtitleDisplayTextEnergyPrice::HasText()
{
	return true;
}

string SubtitleDisplayTextEnergyPrice::GetText()
{
	string outStr = "unknow price";

	for (int idx = 0; idx < _devices.size(); idx++)	
	{
		if (_devices[idx]->_configBase.type == DeviceType_Tibber_Price)
		{
			outStr = "";

			for (int pi = 0; pi<3; pi++)
			{
				int level = _devices[idx]->GetLastReadingInt(pi);
				if (level == 0 || level == 1)
					outStr += DISPLAY_LOGIC_ESC_GREEN;
				else if (level == 2)
					outStr += DISPLAY_LOGIC_ESC_YELLOW;
				else if (level == 3 || level == 4)
					outStr += DISPLAY_LOGIC_ESC_RED;

				int value = (int)(std::round(_devices[idx]->GetLastReadingDouble(pi) * 100.0));
				outStr += string_format("%d", value);
				if (pi < 2)
				{
					outStr += DISPLAY_LOGIC_ESC_LITE_WHITE;
					outStr += DISPLAY_LOGIC_ESC_MSPACE;
					outStr += ">";
					outStr += DISPLAY_LOGIC_ESC_MSPACE;
				}
			}
			outStr += DISPLAY_LOGIC_ESC_LITE_WHITE;
			outStr += "ct";
			break;
		}
	}

	return outStr;
}

