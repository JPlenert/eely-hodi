import { h, Component, Fragment,  FormInput } from "eely-base-web";
import { EspConfigCubit } from "eely-base-web";

// Types for props
interface HoDiTibberCloudSettingsProps {
    configCubit: EspConfigCubit;
};
    
export class HoDiTibberCloudSettings extends Component<HoDiTibberCloudSettingsProps>
{
    render() {
        return (<>
            <FormInput headline="Tibber cloud token" helpInfo="Authorization token for accessing the tibber cloud. Must be gathered from the tibber API portal" bindBase={this.props.configCubit.config} bindPath={"hodi.tibber.token"}></FormInput>
            </>);  
    }
}