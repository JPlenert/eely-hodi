import { h, Component, Fragment, FormCheckBox, FormDropDown, FormDropDownItem, FormInput } from "eely-base-web";
import { EspConfigCubit } from "eely-base-web";

// Types for props
interface HoDiClimateDisplaySettingsProps {
    configCubit: EspConfigCubit;
};

export class HoDiClimateDisplaySettings extends Component<HoDiClimateDisplaySettingsProps>
{
    render() {
        return (<>
            <FormInput headline="Climate display 1" placeHolder="e.g. I$4* A$5*" helpInfo="Format for the climate display. '$n.m' is the device numer, a '*' displays the unit." bindBase={this.props.configCubit.config} bindPath="hodi.climate_1"></FormInput>
            <FormInput headline="Climate display 2" placeHolder="e.g. I$4* A$5*" helpInfo="Format for the climate display. '$n.m' is the device numer, a '*' displays the unit." bindBase={this.props.configCubit.config} bindPath="hodi.climate_2"></FormInput>
            <FormInput headline="Climate display 3" placeHolder="e.g. I$4* A$5*" helpInfo="Format for the climate display. '$n.m' is the device numer, a '*' displays the unit." bindBase={this.props.configCubit.config} bindPath="hodi.climate_3"></FormInput>
            </>);  
    }
}