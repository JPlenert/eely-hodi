import { h, Accordion, AccordionItem, Component, Fragment, FormCheckBox } from "eely-base-web";
import { EspConfigCubit, EspConfigState, tryRegisterCubit } from "eely-base-web";

// Types for props
interface HoDiDisplaySettingsProps {
    configCubit: EspConfigCubit;
};
    
export class HoDiDisplaySetings extends Component<HoDiDisplaySettingsProps>
{
    render() {
        return (<>
            <FormCheckBox headline="Show status subtitle" helpInfo="Enable to show a subtitle if an error occurs." bindBase={this.props.configCubit.config} bindPath={"hodi.display.show_status_subtitle"}></FormCheckBox>
            <FormCheckBox headline="Show RSSI subtitle" helpInfo="Enable to show a subtitle with RSSI wifi signal strength." bindBase={this.props.configCubit.config} bindPath={"hodi.display.show_rssi_subtitle"}></FormCheckBox>
            <FormCheckBox headline="Show energy prices" helpInfo="Enable to show a subtitle with energy prices (from tibber)." bindBase={this.props.configCubit.config} bindPath={"hodi.display.show_energy_price"}></FormCheckBox>
            </>);  
    }
}