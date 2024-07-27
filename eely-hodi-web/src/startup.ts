// Eely-Hodi - (c) 2022-24 by Joerg Plenert | https://eely.eu

/// <reference path="../../../eely-base-web/src/control_basic/Body.ts" />
/// <reference path="../../../eely-base-web/src/control_basic/Div.ts" />
/// <reference path="../../../eely-base-web/src/control_basic/Navbar.ts" />
/// <reference path="../../../eely-base-web/src/control_basic/Accordion.ts" />
/// <reference path="../../../eely-base-web/src/control_basic/AccordionItem.ts" />
/// <reference path="../../../eely-base-web/src/control_esp/FirmwareUpdate.ts" />
/// <reference path="../../../eely-base-web/src/control_esp/WifiSettings.ts" />

window.onload = async () => {

    let url: string = "com";
     //let url: string = "http://10.0.20.50/com"; // Local Dev

    // private url: string = "http://10.0.20.34/com";

    global = globalHoDi = new GlobalHoDi(url);

    try {
        await globalHoDi.updateDeviceInfos();
    } catch { }

    globalHoDi.body = new Body();
    await globalHoDi.body.init();

    let nav = new Navbar("HoDi");
    globalHoDi.body.appendChild(nav);

    nav.addNavItem("bi-house-door", async (ctl) => {
        nav.setProperties("refresh", true, async () => {
            await globalHoDi.updateDeviceInfos();
            nav.switchTo(0);
        });

        ctl.appendChild(new Dashboard());
    });


    nav.addNavItem("bi-gear", async (ctl) => {
        nav.setProperties("refresh", false, null);

        let ac = new Accordion();
        ctl.appendChild(ac);

        var aci = new AccordionItem("Wifi settings");
        ac.appendChild(aci);
        aci.appendChild(new WifiSettings());

        aci = new AccordionItem("Firmware update");
        ac.appendChild(aci);
        aci.appendChild(new FirmwareUpdate());

        aci = new AccordionItem("Info");
        ac.appendChild(aci);

        aci.appendChild(new Div(`(c)2022-24 by Joerg Plenert. Version ` + global.deviceVersion));
    });

    nav.addNavItem("bi-display", async (ctl) => {
        nav.setProperties("refresh", false, null);
        globalHoDi.lastConfig = await globalHoDi.comHodi.configGet();

        if (Object.getOwnPropertyNames(globalHoDi.lastConfig).length == 0) {
            ctl.appendChild(new Div("Not config available, set wifi config first!"));
        }
        else {

            let ac = new Accordion();
            ctl.appendChild(ac);

            var aci = new AccordionItem("Display settings");
            ac.appendChild(aci);
            aci.appendChild(new DisplaySettings());

            aci = new AccordionItem("Shelly cloud settings");
            ac.appendChild(aci);
            aci.appendChild(new ShellyClouldSettings());

            aci = new AccordionItem("Tibber cloud settings");
            ac.appendChild(aci);
            aci.appendChild(new TibberClouldSettings());            

            aci = new AccordionItem("Devices config");
            ac.appendChild(aci);
            aci.appendChild(new DevicesSettings());

            aci = new AccordionItem("Energy display config");
            ac.appendChild(aci);
            aci.appendChild(new EnergyDisplaySettings());

            aci = new AccordionItem("Climate display config");
            ac.appendChild(aci);
            aci.appendChild(new ClimateDisplaySettings());

            var btn = new FormButton("apply config");
            ac.appendChild(btn);
            btn.onClick = async () => {
                await globalHoDi.comHodi.configSet(globalHoDi.lastConfig);

                // No await here - will not respond!
                global.com.restart();
                globalHoDi.body.appendChild(new ModalBox("Resetting ...", "Device will reset now and will start up with new configuration.", false));
            };
        }

    });

    nav.addNavItem("bi-card-text", async (ctl) => {
        nav.setProperties("refresh", false, null);
        globalHoDi.lastConfig = await globalHoDi.comHodi.configGet();
        if (Object.getOwnPropertyNames(globalHoDi.lastConfig).length == 0) {
            ctl.appendChild(new Div("Not config available, set wifi config first!"));
        }
        else {
            ctl.appendChild(new FullConfigSettings());
        }
    });

    nav.addNavItem("bi-arrow-repeat", null, false, 3, "refresh");
    nav.setProperties("refresh", false, null);
    nav.switchTo(0);
}