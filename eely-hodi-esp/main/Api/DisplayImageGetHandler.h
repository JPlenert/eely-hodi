// Eely-HoDi - (c) 2022-26 by Joerg Plenert | https://eely.eu
#ifndef DisplayImageGetHandler_h
#define DisplayImageGetHandler_h

#include <cJSON.h>
#include <string>
#include <ApiHandlerBase.h>
#include "DisplayTask.h"

class DisplayImageGetHandler : public ApiHandlerBase
{
    protected:
        DisplayTask &m_dt;

    public:
        DisplayImageGetHandler(DisplayTask &dt) : m_dt(dt) {}
        Json HandleRequest(Json& request);
        string GetApiId();
};

#endif
