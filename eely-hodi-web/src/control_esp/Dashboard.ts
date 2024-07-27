// Eely-Hodi - (c) 2022-24 by Joerg Plenert | https://eely.eu
/// <reference path="../../../../eely-base-web/src/control_basic/Control.ts" />

class Dashboard extends Control {

    constructor(){
        super();
    }

    private getHeaderValueItem(headerText: string, value: string){
        return `<div class="row row-header"><div class="col row-header-content">${headerText}</div></div>
                <div class="row"><div class="col pad-lr-1"><div class="form-control text-center">${value}</div></div></div>`;
    }
    protected getHtml(): string {
        var rssiString : string;

        if (globalHoDi.lastDeviceInfo.rssi < -90)
            rssiString = globalHoDi.lastDeviceInfo.rssi + " (unusable)";
        else if (globalHoDi.lastDeviceInfo.rssi < -80)
            rssiString = globalHoDi.lastDeviceInfo.rssi + " (not good)";
        else if (globalHoDi.lastDeviceInfo.rssi < -70)
            rssiString = globalHoDi.lastDeviceInfo.rssi + " (fair)";
        else if (globalHoDi.lastDeviceInfo.rssi < -67)
            rssiString = globalHoDi.lastDeviceInfo.rssi + " (good)";
        else
            rssiString = globalHoDi.lastDeviceInfo.rssi + " (Very Good)";

        
        var html = `<div>
        ${this.getHeaderValueItem("HoDi version", globalHoDi.deviceVersion)}
        ${this.getHeaderValueItem("HoDi system status", globalHoDi.lastDeviceInfo.system_status)}
        ${this.getHeaderValueItem("HoDi base status code", globalHoDi.lastDeviceInfo.system_base_status)}
        ${this.getHeaderValueItem("Rssi", rssiString)}`;

        html += `<div class="row row-header"><div class="col row-header-content">Devices</div></div>`;
        html += `<table class="table table-striped">`;
        html += `<thead><tr><th scope="col">#</th><th scope="col">Name</th><th scope="col" >Id</th><th scope="col">Status</th></tr></thead>`;
        html += `<tbody>`;

        if (globalHoDi.lastDeviceInfo.devices.length == 0)
        {
            html += `<tr><td colspan=4>no device!</td></tr>`;
        }
        else
        {
            var no : number = 1;
            globalHoDi.lastDeviceInfo.devices.forEach(element => {

                var status :string;
                if (element.device_last_error == "")
                    status = "OK";
                else
                    status = element.device_last_error;

                html += `<tr>
                <th scope="row">${no}</th>
                <td>${element.device_name}</td>
                <td>${element.device_id}</td>
                <td>${status}</td>
                </tr>`;
                no++;
            });
        }

        html += `</tbody></table></div>`;

        return html;   
    }   
}