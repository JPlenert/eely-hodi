// Eely-HoDi - (c) 2022-24 by Joerg Plenert | https://eely.eu
#ifndef DeviceInfoGetHodiHandler_h
#define DeviceInfoGetHodiHandler_h

#include "DeviceInfoGetHandler.h"

class DeviceInfoGetHodiHandler : public DeviceInfoGetHandler
{
    public:
        DeviceInfoGetHodiHandler() {}

    protected:
        void CollectInfo(Json &repyl);
};

#endif





