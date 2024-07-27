// Eely-Hodi - (c) 2022-24 by Joerg Plenert | https://eely.eu
/// <reference path="../../../../eely-base-web/src/control_basic/Control.ts" />
/// <reference path="../../../../eely-base-web/src/control_basic/FormCheckbox.ts" />
/// <reference path="../../../../eely-base-web/src/control_basic/FormNumber.ts" />

class DisplaySettings extends Control{

    protected initControlLate() {
        var item = new FormCheckbox("Show status subtitle", "Enable to show a subtitle if an error occurs.");
        this.appendChild(item);
        item.bind(globalHoDi.lastConfig, "hodi", "display", "show_status_subtitle")

        var item = new FormCheckbox("Show RSSI subtitle", "Enable to show a subtitle with RSSI wifi signal strength.");
        this.appendChild(item);
        item.bind(globalHoDi.lastConfig, "hodi", "display", "show_rssi_subtitle")

        var item = new FormCheckbox("Show energy prices", "Enable to show a subtitle with energy prices (from tibber).");
        this.appendChild(item);
        item.bind(globalHoDi.lastConfig, "hodi", "display", "show_energy_price")
    }
}