// Eely-HoDi - (c) 2022-24 by Joerg Plenert | https://eely.eu
#include "DisplaySubtitleSetHandler.h"
#include "esp_log.h"

Json DisplaySubtitleSetHandler :: HandleRequest(Json& request)
{
    int duration = request.GetInt("duration");

    if (duration == 0)
        return GetErrorReply(-1, "Duration not set");

    char* text = request.GetCString("text");

    if (!m_dt.SetSubtitleToShow(text, duration))
    {
        free(text);
        return GetErrorReply(-1, "Locked");
    }

    free(text);
    return GetOkReply();
}

string DisplaySubtitleSetHandler :: GetApiId() { return "DisplaySubtitleSet"; }
