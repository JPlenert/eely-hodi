// Eely-Hodi - (c) 2022-24 by Joerg Plenert | https://eely.eu
/// <reference path="../../../../eely-base-web/src/control_basic/Control.ts" />
/// <reference path="../../../../eely-base-web/src/control_basic/FormText.ts" />

class TibberClouldSettings extends Control{

    protected initControlLate() {
        
        var key = new FormText("Tibber cloud token", null, "Authorization token for accessing the tibber cloud. Must be gathered from the tibber API portal");
        this.appendChild(key);
        key.bind(globalHoDi.lastConfig, "hodi", "tibber", "token");
    }
}