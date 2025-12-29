// Eely-Hodi - (c) 2022-25 by Joerg Plenert | https://eely.eu

import { h, Component, ModalController, Navbar, NavbarItem, EspJsonConfigEditor } from "eely-base-web";
import { SymbolGear } from "eely-base-web/components/symbols/symbolGear"
import { SymbolHouseDoor} from "eely-base-web/components/symbols/symbolHouseDoor"
import { SymbolDisplay} from "eely-base-web/components/symbols/symbolDisplay"
import { SymbolCardText} from "eely-base-web/components/symbols/symbolCardText"
import { SymbolArrowRepeat} from "eely-base-web/components/symbols/symbolArrowRepeat"
import { Dashboard } from "./dashboard";
import { HoDiConfigPage } from "./hodiConfigPage";
import { SettingsPage } from "./settingsPage";
import { global } from "../global";
import { doRefreshCallback } from "../refreshCallback";


// Types for props
interface BasePageProps {
};
    
// Types for state
interface BasePageState {
    page: number;
};
  
export class BasePage extends Component<BasePageProps, BasePageState>{

    constructor(props: BasePageProps) {
        super(props);
        this.state = { page : 0 };
      }
    
    render() {
        return (  <div>
          <ModalController/>
          <Navbar headLineText="HoDi" url="https://eely.eu" urlInfo="eely">
        
            <NavbarItem symbolName={SymbolHouseDoor.href} onClick={() => { this.setState({page: 0}) }}/>
            <NavbarItem symbolName={SymbolGear.href} onClick={() => {this.setState({page: 1})}}/>
            <NavbarItem symbolName={SymbolDisplay.href} onClick={() => {this.setState({page: 2})}}/>
            <NavbarItem symbolName={SymbolCardText.href} onClick={() => {this.setState({page: 3})}}/>
            {(this.state.page == 0 || this.state.page == 1) && <NavbarItem symbolName={SymbolArrowRepeat.href} onClick={() => { doRefreshCallback(); }}/>} 
          
            </Navbar>
          
            {this.state.page == 0 && <Dashboard/>}
            {this.state.page == 1 && <SettingsPage/>}
            {this.state.page == 2 && <HoDiConfigPage configCubit={global.configCubit} />}
            {this.state.page == 3 && <EspJsonConfigEditor configCubit={global.configCubit} />}
          
          </div>);
    }
}