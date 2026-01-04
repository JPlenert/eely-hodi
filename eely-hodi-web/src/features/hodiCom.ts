// Eely-Hodi - (c) 2022-26 by Joerg Plenert | https://eely.eu

import { EspCom } from 'eely-base-web';

export interface Device{
    device_last_error: string;
    device_name: string;
    device_id: string;
}
export interface DeviceInfoReply{
    version: string;
    rssi: number;
    status: number;
    system_base_status: number;
    system_status : string;
    devices: Array<Device>;
}

export class HodiCom extends EspCom {

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

    public async device_info_get() : Promise<DeviceInfoReply>{
        let req = { ApiId: "DeviceInfoGet" };
        return await this.post(req);
    }
}