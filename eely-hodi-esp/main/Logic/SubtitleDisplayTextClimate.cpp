// Eely-HoDi - (c) 2022-26 by Joerg Plenert | https://eely.eu
#include "SubtitleDisplayTextClimate.h"
#include "string_format.h"
#include "DisplayLogic.h"


SubtitleDisplayTextClimate::SubtitleDisplayTextClimate(ClimateInfoItem infoItem, vector<DeviceInstance*>& devices) : _infoItem(infoItem), _devices(devices)
{}

bool SubtitleDisplayTextClimate::HasText()
{
	return true;
}

string SubtitleDisplayTextClimate::GetText()
{
	string outStr = "";
	int device_idx = 0;

	for (int idx = 0; idx < _infoItem.text.size(); idx++)
	{
		char ch = _infoItem.text[idx];
		if (ch == '$')
		{
			DeviceInstance* device = _devices[_infoItem.device_index_list[device_idx].device_index - 1];
			double val = device->GetLastReadingDouble(_infoItem.device_index_list[device_idx].value_index);
			
			outStr += string_format("%.0f", val);
			device_idx++;
		}
		else
		{
			outStr += ch;
		}
	}
	return outStr;
}