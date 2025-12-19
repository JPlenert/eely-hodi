// Eely-Hodi - (c) 2022-25 by Joerg Plenert | https://eely.eu

import { h, Accordion, AccordionItem, Component } from "eely-base-web";
import { EspWifiSettings, EspFirmwareUpload, EspResetDevice } from "eely-base-web";
import { global } from "../global";
import { globalHoDiCubit } from "../cubits/hodiCubit";

// Types for props
interface SettingsPageProps {
};
  
// Types for state
export interface SettingsPageState {
};
  
export class SettingsPage extends Component<SettingsPageProps, SettingsPageState>{
    readonly SettingsPage = 'collapsed';
    buttonClass: string;

    constructor(props: SettingsPageProps) {
        super(props);
      }

      render() {
        return (
            <Accordion>
                <AccordionItem headerText="Wifi Settings">
                    <EspWifiSettings com={global.com}/>
                </AccordionItem>
                <AccordionItem headerText="Firmware update">
                    <EspFirmwareUpload com={global.com}/>
                </AccordionItem>
                <AccordionItem headerText="Reset device">
                    <EspResetDevice com={global.com}/>
                </AccordionItem>
                <AccordionItem headerText="Info">
                    <div>(c)2022-25 by Joerg Plenert. Version {globalHoDiCubit.state.lastDeviceInfo.version}</div>
                </AccordionItem>
            </Accordion>
        );
      }
}
