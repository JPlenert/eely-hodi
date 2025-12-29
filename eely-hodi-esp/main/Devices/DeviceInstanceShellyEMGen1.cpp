// Eely-HoDi - (c) 2022-24 by Joerg Plenert | https://eely.eu
#include "DeviceInstanceShellyEMGen1.h"

DeviceInstanceShellyEMGen1 :: DeviceInstanceShellyEMGen1(ConfigDeviceShelly& config) : DeviceInstanceShelly(1, config)
{
	_totalPower = 0;

	_p1Power = 0;
	_p1Voltage = 0;

	_p2Power = 0;
	_p2Voltage = 0;
}

double DeviceInstanceShellyEMGen1::GetLastReadingDouble(int idx)
{
	switch (idx) {
	case 0: return _totalPower;
	case 10: return _p1Power;
	case 12: return _p1Voltage;
	case 20: return _p2Power;
	case 22: return _p2Voltage;
	}
	return 0;
}

int DeviceInstanceShellyEMGen1::GetLastReadingInt(int idx)
{
	return (int)GetLastReadingDouble(idx);
}

bool DeviceInstanceShellyEMGen1::DoSync()
{
	Json status = DeviceInstanceShelly::GetStatus();
	optional<JsonArray> emetersArray;
	optional<Json> jNode;

	if (status.IsEmpty())
	{
		// _lastError was set by GetStatus
		return false;
	}

	emetersArray = status.GetArray("emeters");
	if (!emetersArray.has_value())
	{
		_lastError = "not emeters array";
		return false;
	}
	
	jNode = emetersArray.value().GetFirst();
	if (!jNode.has_value())
	{
		_lastError = "emeter 1 is empty";
		return false;
	}
	_p1Power =  jNode.value().GetDouble("power");
	_p1Voltage = jNode.value().GetDouble("voltage");

	jNode = emetersArray.value().GetNext();
	if (!jNode.has_value())
	{
		_lastError = "emeter 2 is empty";
		return false;
	}
	_p2Power = jNode.value().GetDouble("power");
	_p2Voltage = jNode.value().GetDouble("voltage");

	_totalPower = _p1Power + _p2Power;

	_lastError = "";

	return true;
}