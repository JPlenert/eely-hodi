// Eely-Hodi - (c) 2022-25 by Joerg Plenert | https://eely.eu

import { HodiCom } from './features/hodiCom';
import { EspConfigCubit } from "eely-base-web";

export class Global{
    public com: HodiCom;
    public configCubit : EspConfigCubit;
}

export const global : Global = new Global();