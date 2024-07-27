#include "SubtitleDisplayTextRssi.h"
#include "string_format.h"
#include "DisplayLogic.h"
#include "Eelyapp.h"
#include "esp_wifi.h"

bool SubtitleDisplayTextRssi::HasText()
{
	return true;
}

string SubtitleDisplayTextRssi::GetText()
{
	int rssi;

	if (esp_wifi_sta_get_rssi(&rssi) == ESP_OK)
	{
		if (rssi < -90)
			return string_format("rssi \tCR%d", rssi);
		if (rssi < -80)
			return string_format("rssi \tCr%d", rssi);
		if (rssi < -70)
			return string_format("rssi \tCy%d", rssi);
		if (rssi < -67)
			return string_format("rssi \tCg%d", rssi);
		return string_format("rssi \tCG%d", rssi);
	}
	else
		return "no rssi";
}
