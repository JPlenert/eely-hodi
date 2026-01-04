// Eely-HoDi - (c) 2022-26 by Joerg Plenert | https://eely.eu
#ifndef Display_h
#define Display_h

#define ESP32
#include <MatrixHardware_ESP32_V0.h>  
#include <SmartMatrix.h>

#define DISPLAY_COLOR_DEPTH 24                                  // Choose the color depth used for storing pixels in the layers: 24 or 48 (24 is good for most sketches - If the sketch uses type `rgb24` directly, COLOR_DEPTH must be 24)
#define DISPLAY_MATRIX_WIDTH 64                                 // Set to the width of your display, must be a multiple of 8
#define DISPLAY_MATRIX_HEIGHT 32                                // Set to the height of your display
#define DISPLAY_REFRESH_DEPTH 36                                // Tradeoff of color quality vs refresh rate, max brightness, and RAM usage.  36 is typically good, drop down to 24 if you need to.  On Teensy, multiples of 3, up to 48: 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45, 48.  On ESP32: 24, 36, 48
#define DISPLAY_PANELTYPE SM_PANELTYPE_HUB75_32ROW_MOD16SCAN    // Choose the configuration that matches your panels.  See more details in MatrixCommonHub75.h and the docs: https://github.com/pixelmatix/SmartMatrix/wiki
#define DISPLAY_MATRIX_OPTIONS SM_HUB75_OPTIONS_NONE            // see docs for options: https://github.com/pixelmatix/SmartMatrix/wiki

extern SMLayerBackground<rgb24, 0> backgroundLayer;
extern SmartMatrixHub75Refresh<DISPLAY_REFRESH_DEPTH, DISPLAY_MATRIX_WIDTH, DISPLAY_MATRIX_HEIGHT, DISPLAY_PANELTYPE, DISPLAY_MATRIX_OPTIONS> matrixRefresh;
extern SmartMatrixHub75Calc<DISPLAY_REFRESH_DEPTH, DISPLAY_MATRIX_WIDTH, DISPLAY_MATRIX_HEIGHT, DISPLAY_PANELTYPE, DISPLAY_MATRIX_OPTIONS> matrix;

#endif