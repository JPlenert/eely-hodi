// Eely-HoDi - (c) 2022-24 by Joerg Plenert | https://eely.eu
#ifndef DisplaySubtitleSetHandler_h
#define DisplaySubtitleSetHandler_h

#include <cJSON.h>
#include <string>
#include <ApiHandlerBase.h>
#include "DisplayTask.h"

class DisplaySubtitleSetHandler : public ApiHandlerBase
{
    protected:
        DisplayTask &m_dt;

    public:
        DisplaySubtitleSetHandler(DisplayTask &dt) : m_dt(dt) {}
        Json HandleRequest(Json& request);
        string GetApiId();
};

#endif
