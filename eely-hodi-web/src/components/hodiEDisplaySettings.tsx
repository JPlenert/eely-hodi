import { h, Component, Fragment, FormCheckBox, FormDropDown, FormDropDownItem, FormInput } from "eely-base-web";
import { EspConfigCubit } from "eely-base-web";

// Types for props
interface HoDiEDisplaySettingsProps {
    configCubit: EspConfigCubit;
};

export class HoDiEDisplaySettings extends Component<HoDiEDisplaySettingsProps>
{
    private _displayTypes : FormDropDownItem[] = [
            new FormDropDownItem("None", 0), 
            new FormDropDownItem("Total", 1),
            new FormDropDownItem("Total & production", 2),
            new FormDropDownItem("Total & production & storage", 3),
        ];

    render() {
        return (<>
            <FormDropDown headline="Energy display type" items={this._displayTypes} bindBase={this.props.configCubit.config} bindPath={"hodi.energy.displayType"}></FormDropDown>
            <FormInput headline="Total calculation" placeHolder="e.g. +1.1-2+3" helpInfo="Calculation to build the total energy. Sequence of '+/-' followed by device number and optioally followed by a point and a device data source." bindBase={this.props.configCubit.config} bindPath={"hodi.energy.total"}></FormInput>
            <FormInput headline="Consumption calculation" placeHolder="e.g. +1+3.2" helpInfo="Calculation to build the consumed energy. Format is same as in total calculation." bindBase={this.props.configCubit.config} bindPath={"hodi.energy.consumption"}></FormInput>
            <FormInput headline="Production calculation" placeHolder="e.g. +1+3.2" helpInfo="Calculation to build the produced energy. Format is same as in total calculation." bindBase={this.props.configCubit.config} bindPath={"hodi.energy.production"}></FormInput>
            <FormInput headline="Storage calculation" placeHolder="e.g. +1+3.2" helpInfo="Calculation to build the stored energy. Format is same as in total calculation." bindBase={this.props.configCubit.config} bindPath={"hodi.energy.storage"}></FormInput>
            </>);  
    }
}