// Eely-Hodi - (c) 2022-24 by Joerg Plenert | https://eely.eu
/// <reference path="../../../../eely-base-web/src/control_basic/Control.ts" />
/// <reference path="../../../../eely-base-web/src/control_basic/FormText.ts" />

class ShellyClouldSettings extends Control{

    protected initControlLate() {
        
        var key = new FormText("Cloud authorization key", null, "Authorization key for accessing the shelly cloud. Must be gathered from the shelly portal, normally at User Settings -> Authorization cloud key");
        this.appendChild(key);
        key.bind(globalHoDi.lastConfig, "hodi", "shelly", "authkey");
        var host = new FormText("Cloud host", null, "Cloud hostname from the shelly cloud. The server uri can be obtained on the same page where the authorization key is generated");
        this.appendChild(host);
        host.bind(globalHoDi.lastConfig, "hodi", "shelly", "cloudhost");
    }
}