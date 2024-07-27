// Eely-Hodi - (c) 2022-24 by Joerg Plenert | https://eely.eu
/// <reference path="../../../../eely-base-web/src/control_basic/Control.ts" />
/// <reference path="../../../../eely-base-web/src/control_basic/FormCheckbox.ts" />
/// <reference path="../../../../eely-base-web/src/control_basic/FormNumber.ts" />
/// <reference path="../../../../eely-base-web/src/control_basic/FormText.ts" />
/// <reference path="../../../../eely-base-web/src/control_basic/FormButton.ts" />

class ClimateDisplaySettings extends Control{
    protected initControlLate() {
        
        var item = new FormText("Climate display 1", "e.g. I$4* A$5*", "Format for the climate display. '$n.m' is the device numer, a '*' displays the unit.")
        this.appendChild(item);
        item.bind(globalHoDi.lastConfig, "hodi", "climate_1");

        var item = new FormText("Climate display 2", "e.g. I$4* A$5*", "Format for the climate display. '$n.m' is the device numer, a '*' displays the unit.")
        this.appendChild(item);
        item.bind(globalHoDi.lastConfig, "hodi", "climate_2");

        var item = new FormText("Climate display 3", "e.g. I$4* A$5*", "Format for the climate display. '$n.m' is the device numer, a '*' displays the unit.")
        this.appendChild(item);
        item.bind(globalHoDi.lastConfig, "hodi", "climate_3");
    }
}