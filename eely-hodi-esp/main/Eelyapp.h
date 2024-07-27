// Eely-HoDi - (c) 2022-24 by Joerg Plenert | https://eely.eu
#ifndef Eelyapp_h
#define Eelyapp_h

#include <string>
#include "Eelybase.h"
#include "ConfigStoreApp.h"

class Eelyapp : public Eelybase
{
    public:
        ConfigStoreApp* _configApp;
        static const string FEATKEY_DISPLAYTASK;
        static const string FEATKEY_DEVICETASK;

    private:
        bool _doDisplayVersion;
        bool _hasErroredDevice;
        
    public:
        Eelyapp();
        void Init() override;
        string GetSystemStatusString(bool emptyOnOk) override;
        void setDeviceError(bool hasError);

    protected:
        void InitFeatures() override;          
        void InitConfigStore() override;
        void OnSystemStatusChanged(const char* source) override;
};

extern Eelyapp* g_eelyapp;

#endif