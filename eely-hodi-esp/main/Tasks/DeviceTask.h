// Eely-HoDi - (c) 2022-24 by Joerg Plenert | https://eely.eu
#ifndef ShellyTask_h
#define ShellyTask_h

using namespace std;

#include <list>
#include <string>
#include <vector>
#include "ConfigStoreApp.h"
#include "TaskBase.h"
#include "DeviceInstance.h"

class DeviceTask : public TaskBase
{          
    protected:
        time_t _lastTs;

        // Move Device instance to config? Other other place? So DeviceTask can access is right index-order!
        int _curSyncItemIdx;
        // dynamic list of devices, used for internal priorisation of the data sync
        list<DeviceInstance*> _devicesPrioList;

    public:
        // A 'constant' list of devices, shared with other classes        
        vector<DeviceInstance*> _devicesVector;        

    public:
        DeviceTask(ConfigStoreApp& config);

    protected:
        void ApplyConfig(ConfigStoreApp& config);

        void Work() override;
};


#endif