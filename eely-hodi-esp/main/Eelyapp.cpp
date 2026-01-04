// Eely-HoDi - (c) 2022-26 by Joerg Plenert | https://eely.eu
#include "Eelyapp.h"
#include "DisplayImageSetHandler.h"
#include "DisplaySubtitleSetHandler.h"
#include "DisplayLogic.h"
#include "esp_log.h"
#include "ApiManager.h"
#include "WebServer.h"
#include "SystemTime.h"
#include "SystemMessage.h"
#include "DeviceInfoGetHodiHandler.h"
#include "wifi.h"

#include "DisplayTask.h"
#include "DeviceTask.h"


extern const uint8_t index_html_start[] asm("_binary_index_min_html_start");
extern const uint8_t index_html_end[]   asm("_binary_index_min_html_end");

const string Eelyapp::FEATKEY_DISPLAYTASK = "displaytask";
const string Eelyapp::FEATKEY_DEVICETASK = "devicetask";

#include "ConfigStoreApp.h"

Eelyapp :: Eelyapp()
{
    _doDisplayVersion = true;
    _hasErroredDevice = false;
}

void Eelyapp :: Init()
{
    // Init display first!
    Display_Init();
    Display_Version("init");
    Display_CommitDraw();

    Eelybase::Init();
}

string Eelyapp :: GetSystemStatusString(bool emptyOnOk)
{
    string status = Eelybase::GetSystemStatusString(true);
    if (!status.empty())
        return status;

    status = wifi_status_get_string();
    if (!status.empty())
        return "wifi "+status;

    if (_hasErroredDevice)
        return "device error";

    return emptyOnOk ? "" : "ok";
}

void Eelyapp :: OnSystemStatusChanged(const char* source)
{
    if (!_doDisplayVersion)
        return;

    string status = GetSystemStatusString(false);

    Display_Version(status.c_str());
    ESP_LOGI("DSP", "Status %s", status.c_str());
    Display_CommitDraw();
    
    // Log screen of startup!
    // Display_ScreenshotToLog();

    vTaskDelay(100);    
}

void Eelyapp :: InitFeatures()
{
    Eelybase::InitFeatures();

    Webserver* webServer = (Webserver*)_featureMap[FEATKEY_WEBSERVER];

    webServer->SetIndex((char*)index_html_start, index_html_end - index_html_start);

    int notTimeMgsId = SystemMessage::GetInstance()->AddMessage("Time has not been initialized");

    DeviceTask *deviceTask = new DeviceTask(*_configApp);
    _featureMap[FEATKEY_DEVICETASK] = deviceTask;

    DisplayTask* displayTask = new DisplayTask(*_configApp, deviceTask->_devicesVector);
    _featureMap[FEATKEY_DISPLAYTASK] = displayTask;

    SystemTime* sysTime = SystemTime::GetInstance();
    sysTime->AddTimeInitInfo([&, notTimeMgsId, displayTask, deviceTask] {       
        if (_doDisplayVersion)
        {
            SetBaseStatus(EelybaseStatus_OK);
            SystemMessage::GetInstance()->RemoveMessage(notTimeMgsId);
            _doDisplayVersion = false;
            displayTask->Start();
            deviceTask->Start();
        }
    });

    webServer->AddApi(new DeviceInfoGetHodiHandler());
    webServer->AddApi(new DisplayImageSetHandler(*displayTask));
    webServer->AddApi(new DisplaySubtitleSetHandler(*displayTask));
}

void Eelyapp :: InitConfigStore() 
{ 
    _config = _configApp = new ConfigStoreApp(); 
}

void Eelyapp :: setDeviceError(bool hasError)
{
    _hasErroredDevice = hasError;
}
