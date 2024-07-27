// Eely-Hodi - (c) 2022-24 by Joerg Plenert | https://eely.eu
/// <reference path="../../../../eely-base-web/src/control_basic/Control.ts" />
/// <reference path="../../../../eely-base-web/src/control_basic/FormDropDown.ts" />

class DevicesSettings extends Control {

    private accordion: Accordion;
    private addNewDD: FormDropDown;
    private deviceList: Array<any>;

    protected initControlLate() {
        this.deviceList = globalHoDi.lastConfig?.hodi?.devices;

        this.accordion = new Accordion();
        this.appendChild(this.accordion);

        if (this.deviceList != null) {
            this.deviceList.forEach(element => {
                this.addDevAccordion(element);
            });
        }

        var ddItemd: FormDropDownItem[] = [
            new FormDropDownItem("shelly_3em", "Shelly 3EM"),
            new FormDropDownItem("shelly_pro3em", "Shelly Pro 3EM"),
            new FormDropDownItem("shelly_ht", "Shelly H&T"),
            new FormDropDownItem("shelly_plugs", "Shelly Plug S"),
            new FormDropDownItem("tibber_price", "Tibber Prices"),
        ];

        this.addNewDD = new FormDropDown("Add new item", ddItemd, null, "bi-plus");
        this.accordion.appendChild(this.addNewDD);

        this.addNewDD.onButtonClick = (ctl) => {
            // Currently only "shelly"
            // if (ctl.getValue())           
            var newDevConfig = { type: ctl.getValue(), name: 'new', access: 'direct' };
            if (globalHoDi.lastConfig.hodi == null)
                globalHoDi.lastConfig.hodi = {};
            if (this.deviceList == null) {
                this.deviceList = globalHoDi.lastConfig.hodi.devices = [];
            }
            this.deviceList.push(newDevConfig);
            var newAcItem = this.addDevAccordion(newDevConfig);
            newAcItem.openItem();
        };
    }

    public static getAccordionItemHeaderText(deviceConfig: any): string {
        return `${deviceConfig.name} (${deviceConfig.type})`;
    }

    private addDevAccordion(deviceConfig: any): AccordionItem {
        var devAccordionItem = new AccordionItem(DevicesSettings.getAccordionItemHeaderText(deviceConfig));

        if (this.addNewDD == null)
            this.accordion.appendChild(devAccordionItem);
        else
            this.accordion.insertBeforeChild(devAccordionItem, this.addNewDD);

        if (deviceConfig.type == 'tibber_price')
            devAccordionItem.appendChild(new TibberSettings(deviceConfig));
        else
            devAccordionItem.appendChild(new ShellySettings(deviceConfig));

        devAccordionItem.setAdditionalButton("bi-trash", () => {
            // Find item index
            var foundIdx = -1;

            for (var idx = 0; idx < this.deviceList.length; idx++) {
                if (this.deviceList[idx] === deviceConfig) {
                    foundIdx = idx;
                    break;
                }
            }

            devAccordionItem.htmlElement.remove();
            this.deviceList = this.deviceList.splice(foundIdx, 1);
        });


        return devAccordionItem;
    }
}
