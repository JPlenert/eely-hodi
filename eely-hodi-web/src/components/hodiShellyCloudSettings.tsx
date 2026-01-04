// Eely-Hodi - (c) 2022-26 by Joerg Plenert | https://eely.eu

import { h, Component, Fragment, FormInput } from "eely-base-web";
import { EspConfigCubit } from "eely-base-web";

// Types for props
interface HoDiShellyCloudSettingsProps {
    configCubit: EspConfigCubit;
};
    
export class HoDiShellyCloudSettings extends Component<HoDiShellyCloudSettingsProps>
{
    constructor(props: HoDiShellyCloudSettingsProps)
    {
        super(props);
    }

    render() {
        return (<>
            <FormInput headline="Cloud authorization key" helpInfo="Authorization key for accessing the shelly cloud. Must be gathered from the shelly portal, normally at User Settings -> Authorization cloud key" bindBase={this.props.configCubit.config} bindPath={"hodi.shelly.authkey"}></FormInput>
            <FormInput headline="Cloud host" helpInfo="Cloud hostname from the shelly cloud. The server uri can be obtained on the same page where the authorization key is generated" bindBase={this.props.configCubit.config} bindPath={"hodi.shelly.cloudhost"}></FormInput>
            </>);  
    }
}