// Eely-Hodi - (c) 2022-24 by Joerg Plenert | https://eely.eu

/// <reference path="../../../eely-base-web/src/Global.ts" />

class GlobalHoDi extends Global{
    public lastDeviceInfo: any;
    public lastConfig : any; 
    public comHodi : ComHoDi; 

    constructor(url: string = null){
        super(url);
        this.com = this.comHodi = new ComHoDi(url);
    }

    public async updateDeviceInfos() : Promise<void>{
        let info = await global.com.device_info_get();
        this.lastDeviceInfo = info;
        this.deviceVersion = info.version;
    }
}

var globalHoDi : GlobalHoDi;
