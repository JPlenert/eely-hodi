// Eely-HoDi - (c) 2022-26 by Joerg Plenert | https://eely.eu
#ifndef DeviceInstance_h
#define DeviceInstance_h

using namespace std;

#include <list>
#include <string>
#include "ConfigStoreApp.h"

class DeviceInstance
{
public:
    string _lastError;
    int _continuousSyncErrorCount;
    time_t _lastSyncTs;
    int _syncFrequencyS;
    ConfigDeviceBase& _configBase;

public:
    DeviceInstance(int syncFrequencyS, ConfigDeviceBase& configBase) : _continuousSyncErrorCount(0), _lastSyncTs(0), _syncFrequencyS(syncFrequencyS), _configBase(configBase) {}
    virtual bool DoSync() = 0;
    virtual double GetLastReadingDouble(int idx) { return 0; }
    virtual int GetLastReadingInt(int idx) { return 0; }

    virtual string GetDeviceName() { return "n/a"; };
    virtual string GetDeviceId() { return "n/a"; };
};

#endif