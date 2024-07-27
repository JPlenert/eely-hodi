// Eely-HoDi - (c) 2022-24 by Joerg Plenert | https://eely.eu
#include "DeviceInstanceShellyHT.h"

double DeviceInstanceShellyHT::GetLastReadingDouble(int idx)
{
	if (idx == 0)
		return _lastTempReading;
	else if (idx == 1)
		return _lastHumReading;
	return 0;
}

int DeviceInstanceShellyHT::GetLastReadingInt(int idx) 
{
	return (int)GetLastReadingDouble(idx);
}

bool DeviceInstanceShellyHT::DoSync()
{
	Json status = DeviceInstanceShelly::GetStatus();
	optional<Json> jNode;

	if (status.IsEmpty())
	{
		// _lastError was set bet GetStatus
		return false;
	}
	jNode = status.GetNode("tmp");
	if (!jNode.has_value())
	{
		_lastError = "no 'tmp' node";
		return false;
	}
	_lastTempReading = jNode.value().GetDouble("value");

	jNode = status.GetNode("hum");
	if (!jNode.has_value())
	{
		_lastError = "no 'hum' node";
		return false;
	}
	_lastHumReading = jNode.value().GetDouble("value");

	_lastError = "";

	return true;
}