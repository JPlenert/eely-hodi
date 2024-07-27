// Eely-HoDi - (c) 2022-24 by Joerg Plenert | https://eely.eu
#include "Display.h"

SMLayerBackground<rgb24, 0> backgroundLayer(DISPLAY_MATRIX_WIDTH, DISPLAY_MATRIX_HEIGHT);
SmartMatrixHub75Refresh<DISPLAY_REFRESH_DEPTH, DISPLAY_MATRIX_WIDTH, DISPLAY_MATRIX_HEIGHT, DISPLAY_PANELTYPE, DISPLAY_MATRIX_OPTIONS> matrixRefresh;
SmartMatrixHub75Calc<DISPLAY_REFRESH_DEPTH, DISPLAY_MATRIX_WIDTH, DISPLAY_MATRIX_HEIGHT, DISPLAY_PANELTYPE, DISPLAY_MATRIX_OPTIONS> matrix;
