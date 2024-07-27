// Eely-HoDi - (c) 2022-24 by Joerg Plenert | https://eely.eu
#include "DeviceInstanceShelly3EM.h"

DeviceInstanceShelly3EM :: DeviceInstanceShelly3EM(ConfigDeviceShelly& config) : DeviceInstanceShelly(config)
{
	_totalPower = 0;

	_p1Power = 0;
	_p1Pf = 0;
	_p1Voltage = 0;

	_p2Power = 0;
	_p2Pf = 0;
	_p2Voltage = 0;

	_p3Power = 0;
	_p3Pf = 0;
	_p3Voltage = 0;
}

double DeviceInstanceShelly3EM::GetLastReadingDouble(int idx)
{
	switch (idx) {
	case 0: return _totalPower;
	case 10: return _p1Power;
	case 11: return _p1Pf;
	case 12: return _p1Voltage;
	case 20: return _p2Power;
	case 21: return _p2Pf;
	case 22: return _p2Voltage;
	case 30: return _p2Power;
	case 31: return _p2Pf;
	case 32: return _p2Voltage;
	}
	return 0;
}

int DeviceInstanceShelly3EM::GetLastReadingInt(int idx)
{
	return (int)GetLastReadingDouble(idx);
}

bool DeviceInstanceShelly3EM::DoSync()
{
	Json status = DeviceInstanceShelly::GetStatus();
	optional<JsonArray> emetersArray;
	optional<Json> jNode;

	if (status.IsEmpty())
	{
		// _lastError was set bet GetStatus
		return false;
	}
	_totalPower = status.GetDouble("total_power");
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
	_p1Pf = jNode.value().GetDouble("pf");
	_p1Voltage = jNode.value().GetDouble("voltage");

	jNode = emetersArray.value().GetNext();
	if (!jNode.has_value())
	{
		_lastError = "emeter 2 is empty";
		return false;
	}
	_p2Power = jNode.value().GetDouble("power");
	_p2Pf = jNode.value().GetDouble("pf");
	_p2Voltage = jNode.value().GetDouble("voltage");

	jNode = emetersArray.value().GetNext();
	if (!jNode.has_value())
	{
		_lastError = "emeter 3 is empty";
		return false;
	}
	_p3Power = jNode.value().GetDouble("power");
	_p3Pf = jNode.value().GetDouble("pf");
	_p3Voltage = jNode.value().GetDouble("voltage");

	_lastError = "";

	return true;
}