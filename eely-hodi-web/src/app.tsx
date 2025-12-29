// Eely-Hodi - (c) 2022-25 by Joerg Plenert | https://eely.eu

import { EspConfigCubit, h, render } from "eely-base-web";
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
import { BasePage } from "./components/basePage";
import "./my.css"; 

render(<BasePage />, document.body)

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
