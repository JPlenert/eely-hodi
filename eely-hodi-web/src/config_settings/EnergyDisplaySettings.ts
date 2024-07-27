// Eely-Hodi - (c) 2022-24 by Joerg Plenert | https://eely.eu
/// <reference path="../../../../eely-base-web/src/control_basic/Control.ts" />
/// <reference path="../../../../eely-base-web/src/control_basic/FormCheckbox.ts" />
/// <reference path="../../../../eely-base-web/src/control_basic/FormNumber.ts" />
/// <reference path="../../../../eely-base-web/src/control_basic/FormText.ts" />
/// <reference path="../../../../eely-base-web/src/control_basic/FormButton.ts" />

class EnergyDisplaySettings extends Control{
    protected initControlLate() {
        
        var displayTypes : FormDropDownItem[] = [
            new FormDropDownItem("0", "None"), 
            new FormDropDownItem("1", "Total"),
            new FormDropDownItem("2", "Total & production"),
            new FormDropDownItem("3", "Total & production & storage"),
        ];

        var dd = new FormDropDown("Energy display type", displayTypes, null, null );
        this.appendChild(dd);
        dd.bind(globalHoDi.lastConfig, "hodi" ,"energy", "displayType");

        var item = new FormText("Total calculation", "e.g. +1.1-2+3", "Calculation to build the total energy. Sequence of '+/-' followed by device number and optioally followed by a point and a device data source.")
        this.appendChild(item);
        item.bind(globalHoDi.lastConfig, "hodi", "energy", "total");

        var item = new FormText("Consumption calculation", "e.g. +1+3.2", "Calculation to build the consumed energy. Format is same as in total calculation.")
        this.appendChild(item);
        item.bind(globalHoDi.lastConfig, "hodi", "energy", "consumption");

        var item = new FormText("Production calculation", "e.g. +1+3.2", "Calculation to build the produced energy. Format is same as in total calculation.")
        this.appendChild(item);
        item.bind(globalHoDi.lastConfig, "hodi", "energy", "production");

        var item = new FormText("Storage calculation", "e.g. +1+3.2", "Calculation to build the stored energy. Format is same as in total calculation.")
        this.appendChild(item);
        item.bind(globalHoDi.lastConfig, "hodi", "energy", "storage");
    }
}