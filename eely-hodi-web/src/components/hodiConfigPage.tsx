// Eely-Hodi - (c) 2022-26 by Joerg Plenert | https://eely.eu

import { h, Fragment, Accordion, AccordionItem, Component, EspEDeviceSettingsMulti, ModalBox, tryRegisterCubit } from "eely-base-web";
import { HoDiDisplaySetings } from "./hodiDisplaySettings";
import { HoDiShellyCloudSettings } from "./hodiShellyCloudSettings";
import { HoDiTibberCloudSettings } from "./hodiTibberCloudSettings";
import { HoDiEDisplaySettings } from "./hodiEDisplaySettings";
import { HoDiClimateDisplaySettings } from "./hodiClimateDisplaySettings";
import { global } from "../global";

import { EspConfigCubit, EspConfigState } from "eely-base-web";

// Types for props
interface HoDiConfigPageProps {
    configCubit: EspConfigCubit;
};
    
// Types for state
interface HoDiConfigPageState {
    meterCollapsed: boolean;
};
  
export class HoDiConfigPage extends Component<HoDiConfigPageProps, HoDiConfigPageState>{
    readonly SettingsPage = 'collapsed';
    buttonClass: string;

    constructor(props: HoDiConfigPageProps) {
        super(props);
        this.state = { meterCollapsed : true };

        if (props.configCubit.config == null)
            props.configCubit.getConfig();                
      }

    render() {
        tryRegisterCubit<EspConfigCubit, EspConfigState>(this, this.props.configCubit);

        if (this.props.configCubit.state.state == EspConfigState.ConfigState_Ready){
            return (
                <>
                <Accordion>
                    <AccordionItem headerText="Display Settings">
                        <HoDiDisplaySetings configCubit={this.props.configCubit}/>
                    </AccordionItem>
                    <AccordionItem headerText="Shelly Cloud Settings">
                        <HoDiShellyCloudSettings configCubit={this.props.configCubit}/>
                    </AccordionItem>
                    <AccordionItem headerText="Tibber Cloud Settings">
                        <HoDiTibberCloudSettings configCubit={this.props.configCubit}/>
                    </AccordionItem>
                    <AccordionItem headerText="Meter devices" collapsed={this.state.meterCollapsed} collapsedChange={(a) => this.setState({ meterCollapsed: a})}>
                        { !this.state.meterCollapsed && 
                        <EspEDeviceSettingsMulti configCubit={global.configCubit} /> }
                    </AccordionItem> 
                    <AccordionItem headerText="Energy Display Settings">
                        <HoDiEDisplaySettings configCubit={this.props.configCubit}/>
                    </AccordionItem>
                    <AccordionItem headerText="Climate Display Settings">
                        <HoDiClimateDisplaySettings configCubit={this.props.configCubit}/>
                    </AccordionItem>
                </Accordion>
                <div style="float: right"><br/>
                    <button type="submit" class="btn btn-primary" onClick={() => { this.props.configCubit.setConfig(); }}> apply config</button>
                </div>
                </>
            );            
        }
        else if (this.props.configCubit.state.state == EspConfigState.ConfigState_NeedReset)
        {
            this.props.configCubit.resetDeviceAndShowModalBox("Device will reset now and will start up with new configuration.");
            return (<>Do reset</>);
        }
        else 
        {   
            return (<>Working ....</>);
        }
    }
}
