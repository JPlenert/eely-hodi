// Eely-Hodi - (c) 2022-25 by Joerg Plenert | https://eely.eu

import { h, Component, Fragment, tryRegisterCubit } from "eely-base-web";
import { HeaderValueItem, getRssiLabel } from "eely-base-web";
import { HoDiCubit, HoDiState, globalHoDiCubit } from "../cubits/hodiCubit"
import { setRefreshCallback } from "../app";
import { EspEDeviceList } from "eely-base-web";

export class Dashboard extends Component {

    constructor() {
        super();
        setRefreshCallback(() => globalHoDiCubit.updateDeviceInfos());
      }

      render() {
        tryRegisterCubit<HoDiCubit, HoDiState>(this, globalHoDiCubit);

        // Display "Loading" unless first get from device is active
        if (globalHoDiCubit.state.lastDeviceInfo == null)
            return <>Loading ....</>;
    
        return (
            <>
                <HeaderValueItem headerText="HoDi version" value={globalHoDiCubit.state.lastDeviceInfo.version}/>
                <HeaderValueItem headerText="HoDi system status" value={globalHoDiCubit.state.lastDeviceInfo.system_status}/>
                <HeaderValueItem headerText="HoDi base status code" value={globalHoDiCubit.state.lastDeviceInfo.system_base_status.toString()}/>
                <HeaderValueItem headerText="WLAN Signalstärke" value={getRssiLabel(globalHoDiCubit.state.lastDeviceInfo.rssi)}></HeaderValueItem>
                <EspEDeviceList list={globalHoDiCubit.state.lastDeviceInfo.devices}></EspEDeviceList>
            </>
            );
    }
}
