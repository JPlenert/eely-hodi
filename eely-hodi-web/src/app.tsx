// Eely-Hodi - (c) 2022-25 by Joerg Plenert | https://eely.eu

import { EspConfigCubit, EspJsonConfigEditor, h, Fragment, ModalController, render, useState } from "eely-base-web";
import { Navbar, NavbarItem } from "eely-base-web";
import { globalHoDiCubit } from "./cubits/hodiCubit";
import { symbolList } from "eely-base-web";
import { SymbolTrash } from "eely-base-web/components/symbols/symbolTrash"
import { SymbolGear } from "eely-base-web/components/symbols/symbolGear"
import { SymbolHome } from "eely-base-web/components/symbols/symbolHome"
import { SymbolHouseDoor} from "eely-base-web/components/symbols/symbolHouseDoor"
import { SymbolDisplay} from "eely-base-web/components/symbols/symbolDisplay"
import { SymbolCardText} from "eely-base-web/components/symbols/symbolCardText"
import { SymbolArrowRepeat} from "eely-base-web/components/symbols/symbolArrowRepeat"
import { SymbolPlus} from "eely-base-web/components/symbols/symbolPlus"

import { global } from "./global";
import { HodiCom } from "./features/hodiCom";
import { Dashboard } from "./components/dashboard";
import { HoDiConfigPage } from "./components/hodiConfigPage";
import { SettingsPage } from "./components/settingsPage";
import "./my.css";

let refreshCallback : () => void;
export function setRefreshCallback(cb : () => void) {
  refreshCallback = cb;
}


// App Component
const App = () =>{ 
  
    const [page, setPage] = useState(0);
  
    return (

  <div>
  <ModalController/>
  <Navbar headLineText="HoDi" url="https://eely.eu" urlInfo="eely">

    <NavbarItem symbolName={SymbolHouseDoor.href} onClick={() => {setPage(0)}}/>
    <NavbarItem symbolName={SymbolGear.href} onClick={() => {setPage(1)}}/>
    <NavbarItem symbolName={SymbolDisplay.href} onClick={() => {setPage(2)}}/>
    <NavbarItem symbolName={SymbolCardText.href} onClick={() => {setPage(3)}}/>
    {(page == 0 || page == 1) && <NavbarItem symbolName={SymbolArrowRepeat.href} onClick={() => { refreshCallback(); }}/>} 
  
    </Navbar>
  
    {page == 0 && <Dashboard/>}
    {page == 1 && <SettingsPage/>}
    {page == 2 && <HoDiConfigPage configCubit={global.configCubit} />}
    {page == 3 && <EspJsonConfigEditor configCubit={global.configCubit} />}
  
  </div>
  )}

  

render(<App />, document.body)

window.onload = async () => {
  var url = "com";
  if (location.hash.startsWith("#testip=")){
    url = `http://${location.hash.substring(8)}/com`;
  }
  console.info(`Using URL ${url}`);
  
  symbolList.init();
  symbolList.addSvg(new SymbolArrowRepeat());
  symbolList.addSvg(new SymbolTrash());
  symbolList.addSvg(new SymbolGear());
  symbolList.addSvg(new SymbolHouseDoor());
  symbolList.addSvg(new SymbolHome());
  symbolList.addSvg(new SymbolDisplay());
  symbolList.addSvg(new SymbolCardText());
  symbolList.addSvg(new SymbolPlus());

  global.com = new HodiCom(url);
  
  global.configCubit = new EspConfigCubit(global.com);

  setTimeout(() => globalHoDiCubit.updateDeviceInfos(), 100);  
}
