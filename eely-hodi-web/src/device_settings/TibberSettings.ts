// Eely-Hodi - (c) 2022-24 by Joerg Plenert | https://eely.eu

class TibberSettings extends Control{

    private config : any;

    constructor(config: any){
        super();
        this.config = config;        
    }

    protected initControlLate() {
        var item = new FormText("Name or description of tibber connection", "Name or description", null);
        this.appendChild(item);
        item.bind(this.config, "name");
        item.onChanged = () => { (<AccordionItem>this.parentControl).setHeaderText(DevicesSettings.getAccordionItemHeaderText(this.config)); }

        this.handleVisibility();
    }

    protected handleVisibility(){
    }
}