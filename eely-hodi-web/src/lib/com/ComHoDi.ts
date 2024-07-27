// Eely-Hodi - (c) 2022-24 by Joerg Plenert | https://eely.eu

/// <reference path="../../../../../eely-base-web/src/lib/com/Com.ts" />
/// <reference path="../types/raw_request.ts"/>

class ComHoDi extends Com {

    constructor(url : string = null) {
        super(url);
    }

    public async configGet() : Promise<any>{
        let req = { ApiId: "ConfigGet" };
        return (await this.post(req)).config;
    }

    public async configSet(config: any) : Promise<any>{
        let req = { ApiId: "ConfigSet", config: config};
        return await this.post(req);
    }

    public async wifi_settings_set(ssid: string, password: string) : Promise<void>{
        let req = { ApiId: "WifiSettingsSet",  ssid: ssid, password: password };
        return await this.post(req);
    }

    public async device_info_get() : Promise<any>{
        let req = { ApiId: "DeviceInfoGet" };
        return await this.post(req);
    }
}