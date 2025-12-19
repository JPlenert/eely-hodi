// Eely-HoDi - (c) 2022-25 by Joerg Plenert | https://eely.eu
#include "DeviceInstanceShellyProEM.h"

DeviceInstanceShellyProEM :: DeviceInstanceShellyProEM(ConfigDeviceShelly& config) : DeviceInstanceShelly(config)
{
	_totalPower = 0;

	_p1Power = 0;
	_p1Pf = 0;
	_p1Voltage = 0;

	_p2Power = 0;
	_p2Pf = 0;
	_p2Voltage = 0;
}

double DeviceInstanceShellyProEM::GetLastReadingDouble(int idx)
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

int DeviceInstanceShellyProEM::GetLastReadingInt(int idx)
{
	return (int)GetLastReadingDouble(idx);
}

bool DeviceInstanceShellyProEM::DoSync()
{
	Json status = DeviceInstanceShelly::GetStatus();
	optional<Json> jNode;

	if (status.IsEmpty())
	{
		// _lastError was set by GetStatus
		return false;
	}

	jNode = status.GetNode("em1:0");
	if (!jNode.has_value())
	{
		_lastError = "not em1:0";
		return false;
	}

	_p1Power =  jNode.value().GetDouble("act_power");
	_p1Pf = jNode.value().GetDouble("pf");
	_p1Voltage = jNode.value().GetDouble("voltage");

	jNode = status.GetNode("em1:1");
	if (!jNode.has_value())
	{
		_lastError = "not em1:1";
		return false;
	}

	_p2Power =  jNode.value().GetDouble("act_power");
	_p2Pf = jNode.value().GetDouble("pf");
	_p2Voltage = jNode.value().GetDouble("voltage");

	_totalPower = _p1Power + _p2Power;

	_lastError = "";

	return true;
}