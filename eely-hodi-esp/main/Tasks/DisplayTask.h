// Eely-HoDi - (c) 2022-24 by Joerg Plenert | https://eely.eu
#ifndef DisplayTask_h
#define DisplayTask_h

#include <TaskBase.h>
#include <string>
#include <functional>
#include "ConfigStoreApp.h"
#include "DeviceInstance.h"
#include "Logic/SubtitleDisplayTextBase.h"

using namespace std;

class DisplayTask : public TaskBase
{   
    private: 
        time_t _lastTS;

        int _imageShowDuration;
        time_t _imageShowTS;
        unsigned char* _imageToShow;

        int _subtitleShowDuration;
        time_t _subtitleShowTS;

        string _subtitleToShow;
        string _subtitleToShowCurrent;

        vector<SubtitleDisplayTextBase*> _defaultSubtitleScreens;

        int _defaultSubtitleIndex;
        int _defaultSubtitleShowTime;

        ConfigStoreApp& _config;
        vector<DeviceInstance*>& _devices;
            
        int _wifiErrorCount;
        int _deviceErrorCount;

    public:
        DisplayTask(ConfigStoreApp& config, vector<DeviceInstance*>& devices);
        bool SetImageToShow(unsigned char* image, int duration);
        bool SetSubtitleToShow(char* subtitle, int duration);

        void OnSettingsChanged();

    protected:
        void PreWork();
        void Work();
};

#endif