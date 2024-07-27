// Eely-HoDi - (c) 2022-24 by Joerg Plenert | https://eely.eu
#include "Eelyapp.h"

Eelyapp *g_eelyapp;

void app_main_cpp()
{
    g_eelybase = g_eelyapp = new Eelyapp();
    g_eelyapp->Init();
}

extern "C"
{
    void app_main(void)
    {
        app_main_cpp();
    }
}


