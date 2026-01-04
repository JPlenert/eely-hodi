// Eely-HoDi - (c) 2022-26 by Joerg Plenert | https://eely.eu
#ifndef DisplayImageSetHandler_h
#define DisplayImageSetHandler_h

#include <cJSON.h>
#include <string>
#include <ApiHandlerBase.h>
#include "DisplayTask.h"

class DisplayImageSetHandler : public ApiHandlerBase
{
    protected:
        DisplayTask &m_dt;

    public:
        DisplayImageSetHandler(DisplayTask &dt) : m_dt(dt) {}
        Json HandleRequest(Json& request);
        string GetApiId();
};

#endif
