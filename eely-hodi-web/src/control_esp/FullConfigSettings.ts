// Eely-Hodi - (c) 2022-24 by Joerg Plenert | https://eely.eu
/// <reference path="../../../../eely-base-web/src/control_basic/Control.ts" />
/// <reference path="../../../../eely-base-web/src/control_basic/FormTextArea.ts" />

class FullConfigSettings extends Control{

    private config : FormTextArea;

    protected initControlLate() {
        
        this.config = new FormTextArea("Json configuration", "<b>Warning! Only set if you exacly know that you are doing!");
        this.appendChild(this.config);

        this.config.setValue(JSON.stringify(globalHoDi.lastConfig.hodi, null, 2));

        var btn = new FormButton("apply config");
        this.appendChild(btn);
        btn.onClick = () => {            
            this.apply();
        };

    }

    private async apply(){
        var jsonVal : any;
            
        try
        {
            jsonVal = JSON.parse(this.config.getValue());
        }
        catch(e)
        {
            globalHoDi.body.appendChild(new ModalBox("Full json config", "Json is invalid", true));
            return;
        }
        globalHoDi.lastConfig.hodi = jsonVal;

        await globalHoDi.comHodi.configSet(globalHoDi.lastConfig);

        // No await here - will not respond!
        global.com.restart();
        globalHoDi.body.appendChild(new ModalBox("Resetting ...", "Device will reset now and will start up with new configuration.", false));
    }
}


