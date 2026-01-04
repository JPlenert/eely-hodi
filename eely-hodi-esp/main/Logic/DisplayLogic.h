// Eely-HoDi - (c) 2022-26 by Joerg Plenert | https://eely.eu
#ifndef DisplayLogic_h
#define DisplayLogic_h

#include <string>

using namespace std;

#define DISPLAY_LOGIC_ESC_MSPACE "\t "
#define DISPLAY_LOGIC_ESC_LITE_GREEN "\tCg"
#define DISPLAY_LOGIC_ESC_GREEN "\tCG"
#define DISPLAY_LOGIC_ESC_LITE_BLUE "\tCg"
#define DISPLAY_LOGIC_ESC_BLUE "\tCG"
#define DISPLAY_LOGIC_ESC_LITE_RED "\tCr"
#define DISPLAY_LOGIC_ESC_RED "\tCR"
#define DISPLAY_LOGIC_ESC_LITE_YELLOW "\tCy"
#define DISPLAY_LOGIC_ESC_YELLOW "\tCY"
#define DISPLAY_LOGIC_ESC_LITE_WHITE "\tCw"
#define DISPLAY_LOGIC_ESC_WHITE "\tCW"

void Display_Init();
void Display_DrawTime(int hour, int minute, int second, bool hugeDigits, int dividerLeft, int dividerRight);
void Display_DrawSubtitle(const char *subtitle, bool centered = false);
void Display_CommitDraw();
void Display_ShowImage(unsigned char *image);
void Display_Version(string status);
void Display_ScreenshotToLog();

#endif