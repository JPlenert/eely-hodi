// Eely-HoDi - (c) 2022-26 by Joerg Plenert | https://eely.eu
#include "DeviceInstanceShellyPro3EM.h"

DeviceInstanceShellyPro3EM :: DeviceInstanceShellyPro3EM(ConfigDeviceShelly& config) : DeviceInstanceShelly(2, config)
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

double DeviceInstanceShellyPro3EM::GetLastReadingDouble(int idx)
{
	switch (idx) {
	case 0: return _totalPower;
	case 10: return _p1Power;
	case 11: return _p1Pf;
	case 12: return _p1Voltage;
	case 20: return _p2Power;
	case 21: return _p2Pf;
	case 22: return _p2Voltage;
	case 30: return _p3Power;
	case 31: return _p3Pf;
	case 32: return _p3Voltage;
	}
	return 0;
}

int DeviceInstanceShellyPro3EM::GetLastReadingInt(int idx)
{
	return (int)GetLastReadingDouble(idx);
}

bool DeviceInstanceShellyPro3EM::DoSync()
{
	Json status = DeviceInstanceShelly::GetStatus();
	optional<Json> jNode;

	if (status.IsEmpty())
	{
		// _lastError was set by GetStatus
		return false;
	}

	jNode = status.GetNode("em:0");
	if (!jNode.has_value())
	{
		_lastError = "not em:0";
		return false;
	}

	_totalPower = jNode.value().GetDouble("total_act_power");

	_p1Power =  jNode.value().GetDouble("a_act_power");
	_p1Pf = jNode.value().GetDouble("a_pf");
	_p1Voltage = jNode.value().GetDouble("a_voltage");

	_p2Power =  jNode.value().GetDouble("b_act_power");
	_p2Pf = jNode.value().GetDouble("b_pf");
	_p2Voltage = jNode.value().GetDouble("b_voltage");

	_p3Power =  jNode.value().GetDouble("c_act_power");
	_p3Pf = jNode.value().GetDouble("c_pf");
	_p3Voltage = jNode.value().GetDouble("c_voltage");

	_lastError = "";

	return true;
}