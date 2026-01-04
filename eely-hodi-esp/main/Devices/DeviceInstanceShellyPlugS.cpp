// Eely-HoDi - (c) 2022-26 by Joerg Plenert | https://eely.eu
#include "DeviceInstanceShellyPlugS.h"
#include "esp_log.h"

DeviceInstanceShellyPlugS ::DeviceInstanceShellyPlugS(ConfigDeviceShelly &config) : DeviceInstanceShelly(2, config)
{
	_power = 0;
	_voltage = 0;
}

double DeviceInstanceShellyPlugS::GetLastReadingDouble(int idx)
{
	switch (idx)
	{
	case 0: return _power;
	case 1: return _voltage;
	}
	return 0;
}

int DeviceInstanceShellyPlugS::GetLastReadingInt(int idx)
{
	return (int)GetLastReadingDouble(idx);
}

bool DeviceInstanceShellyPlugS::DoSync()
{
	Json status = DeviceInstanceShelly::GetStatus();
	optional<JsonArray> emetersArray;
	optional<Json> jNode;

	if (status.IsEmpty())
	{
		// _lastError was set bet GetStatus
		return false;
	}
	optional<Json> switch0 = status.GetNode("switch:0");
	if (!switch0.has_value())
	{
		_lastError = "not switch0 node";
		return false;
	}

	_power = switch0.value().GetDouble("apower");
	_voltage = switch0.value().GetDouble("avoltage");

	_lastError = "";

	return true;
}