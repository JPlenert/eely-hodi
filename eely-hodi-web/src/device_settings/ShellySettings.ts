// Eely-Hodi - (c) 2022-24 by Joerg Plenert | https://eely.eu

class ShellySettings extends Control{

    private check : FormCheckbox;
    private config : any;

    private accessDD : FormDropDown;
    private hostBox : FormText;
    private usernameBox : FormText;
    private passwordBox : FormText;


    constructor(config: any){
        super();
        this.config = config;        
    }

    protected initControlLate() {
        var item = new FormText("Name or description of device", "Name or description", null);
        this.appendChild(item);
        item.bind(this.config, "name");
        item.onChanged = () => { (<AccordionItem>this.parentControl).setHeaderText(DevicesSettings.getAccordionItemHeaderText(this.config)); }

        item = new FormText("Id of the device", "Series of number and characters (hex)", null);
        this.appendChild(item);
        item.bind(this.config, "id");

        this.accessDD = new FormDropDown("Access type", [new FormDropDownItem("direct", "Direct"), new FormDropDownItem("cloudAPI", "Shelly Cloud API") ], null, null );
        this.appendChild(this.accessDD);
        this.accessDD.bind(this.config, "access");

        this.accessDD.onChanged = (ctl) => {
            this.handleVisibility();
        }

        this.hostBox = new FormText("Hostname", null, "Name or IP address of the shelly device");
        this.appendChild(this.hostBox);
        this.hostBox.bind(this.config, "host");

        this.usernameBox = new FormText("Username", null, "Username for the shelly device");
        this.appendChild(this.usernameBox);
        this.usernameBox.bind(this.config, "username");

        this.passwordBox = new FormText("Password", null, "Password for the shelly device");
        this.appendChild(this.passwordBox);
        this.passwordBox.bind(this.config, "password");

        this.handleVisibility();
    }

    protected handleVisibility(){
        var isVisible : boolean = this.accessDD.getValue() == "direct";
        this.hostBox.setVisibility(isVisible);                     
        this.usernameBox.setVisibility(isVisible);                     
        this.passwordBox.setVisibility(isVisible);   
    }
}