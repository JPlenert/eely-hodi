// Eely-Hodi - (c) 2022-26 by Joerg Plenert | https://eely.eu

import { global }  from '../global';
import { CubitBase } from "eely-base-web";
import { DeviceInfoReply }  from '../features/hodiCom';

export class HoDiState {

    lastDeviceInfo: DeviceInfoReply;

    public static fromDeviceInfoReply(reply: DeviceInfoReply) : HoDiState{
        var ret = new HoDiState();
        ret.lastDeviceInfo = reply;

        return ret;        
    } 
}

export class HoDiCubit extends CubitBase<HoDiState>{
    constructor() {
      super(new HoDiState());
    }
  
    public async updateDeviceInfos() : Promise<void>{
      let info = await global.com.device_info_get();
  
      this.emit(HoDiState.fromDeviceInfoReply(info));
    }    
  }
  
  export let globalHoDiCubit : HoDiCubit = new HoDiCubit();
  