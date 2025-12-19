# eely-HoDi

Home of the Eely Home Display (HoDi) (https://www.eely.eu).

![](https://eely.eu/hodi_energy_big_positive.png)

HoDi is a 64x32 matrix LED display driven by a ESP32 that shows:

* the current time
* energy consumptions (with shelly sensors)
* energy productions (with shelly sensors)
* temperatures (with shelly sensors)
* energy prices (with tibber)

## How to build


* Clone repository with `--recursive` to clone the submodules
* Install esbuild with `npm install` in the web folder

* Build eely-hodi-web for release
* Build eely-hodi-esp

Uses ESP-IDF V5.3 for espressif ESP32.

## Remark

This a private hobbyist (aka maker) project that helps me to ['sharpen the saw'](https://blog.codinghorror.com/sharpening-the-saw/) as a Director of a Software innovation unit.
Since I'm more a "backend guy" (white characters on black screen), the frontend is a really "quick and DIRTY" implementation!

## License

eely-HoDi is distributed under the GPL v3 license:

    Copyright (C) 2022-2025 by Joerg Plenert

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, in version 3 of the License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
