// Eely-HoDi - (c) 2022-24 by Joerg Plenert | https://eely.eu
#include "DisplayImageSetHandler.h"
#include "esp_log.h"

Json DisplayImageSetHandler :: HandleRequest(Json& request)
{
    int duration = request.GetInt("duration");

    if (duration == 0)
        return GetErrorReply(-1, "Duration not set");

    size_t imagelen;
    unsigned char* image = request.GetBinary("image", &imagelen);

    if (imagelen != 64*32/2)
    {
        if (image != NULL)
            free(image);
        return GetErrorReply(-1, "Invalid image size");
    }

    if (!m_dt.SetImageToShow(image, duration))
    {
        free(image);
        return GetErrorReply(-1, "Locked");
    }

    return GetOkReply();
}

string DisplayImageSetHandler :: GetApiId() { return "DisplayImageSet"; }
