// Eely-HoDi - (c) 2022-24 by Joerg Plenert | https://eely.eu
#include "DisplayLogic.h"
#include "string.h"
#include "esp_log.h"
#include "Display.h"
#include "Segment7.h"
#include "Segment7Large.h"
#include "esp_idf_version.h"
#include <esp_app_desc.h>

static const char *TAG = "DisplayLogic";
void Display_DrawTextXCentered(int y, rgb24& startColor, const char* text);

#define DISPLAY_ENABLE

void Display_Init()
{
#ifdef DISPLAY_ENABLE
    // setup matrix
    matrix.addLayer(&backgroundLayer); 
    matrix.begin();

    rgb24 fullRed = rgb24(0xff, 0, 0);
    rgb24 white = rgb24(0xff, 0xff, 0xff);
    rgb24 black = rgb24(0, 0, 0);

    rgb24 g = rgb24(0, 0xff, 0);
    rgb24 b = rgb24(0, 0, 0xff);

    backgroundLayer.fillScreen(black);

    matrix.setBrightness(50);

    Display_DrawTime(0, 0, 0, false, 0, 0);
#endif
}

void Display_Version(string status)
{
#ifdef DISPLAY_ENABLE
    rgb24 black = rgb24(0, 0, 0);
    rgb24 fullblue = rgb24(0, 0, 0xff);
    rgb24 liteblue = rgb24(0, 0, 0x8f);
    rgb24 green = rgb24(0, 0x7f, 0);
    rgb24 litewhite = rgb24(0x7f, 0x7f, 0x7f);

    backgroundLayer.fillScreen(black);
    backgroundLayer.setFont(gohufont11b);
    //backgroundLayer.drawString(5, 1, fullblue, "eely.eu");
    Display_DrawTextXCentered(1, fullblue, "eely.eu");

    char versionStr[50];
    sprintf(versionStr, "hodi v%s", esp_app_get_description()->version);
    // cat off patchlevel (no space ...)    
    *strrchr(versionStr, '.') = 0;

    backgroundLayer.setFont(font5x7);
    Display_DrawTextXCentered(11, liteblue, versionStr);

    backgroundLayer.setFont(font3x5);
    if (status.empty())
        Display_DrawTextXCentered(21, litewhite, "starting....");
    else
        Display_DrawTextXCentered(21, green, status.c_str());
#endif
}

void Display_DrawTime(int hour, int minute, int second, bool hugeDigits, int dividerLeft, int dividerRight)
{
#ifdef DISPLAY_ENABLE
    rgb24 fullRed = rgb24(0xff, 0, 0);
    rgb24 black = rgb24(0, 0, 0);

    backgroundLayer.fillScreen(black);

    int digits[] = {hour/10, -1, hour%10, 10, minute/10, -1, minute%10, 10, second/10, -1, second%10};
    
    if (dividerLeft > 0)
        digits[3] = 11 + dividerLeft % 2;
    if (dividerRight > 0)
        digits[7] = 11 + dividerRight % 2;

    if (hugeDigits)    
        Segment7Large_Draw(1, 1, 11, digits, fullRed);
    else
        Segment7_Draw(1, 1, 11, digits, fullRed);
#endif
}

void Display_CommitDraw()
{
#ifdef DISPLAY_ENABLE
    backgroundLayer.swapBuffers(false);
#endif
}

void Display_ScreenshotToLog()
{
    char* buffer = (char*)malloc(2+32*64+1);
    backgroundLayer.screenShot(buffer);
    ESP_LOGI(TAG, "screen shot %s", buffer);
    free(buffer);
}

void Display_DrawTextX_Internal(int& x, int y, rgb24& startColor, const char* text, bool onlyMeasure)
{
#ifdef DISPLAY_ENABLE
    int offset = 0;
    char character;
    rgb24& color = startColor;
    bitmap_font* curFont = backgroundLayer.getCurrentFont();
    int escStatus = 0;

    while ((character = text[offset++]) != '\0') {
        if (character == 9) 
        {
            escStatus = 1;
            continue;
        }

        if (escStatus != 0)
        {
            // error!
            if (character == 0)
            return;

            // Micro-Space
            if (escStatus == 1 && character == ' ')
            {
                x++;
                escStatus = 0;
                continue;
            }

            if (escStatus == 1 && character == 'C')
            {
                escStatus = 'C';
                continue;
            }

            if (escStatus == 'C')
            {
                if (character == 'g')
                    color = rgb24(0, 0x7f, 0);
                else if (character == 'G')
                    color = rgb24(0, 0xff, 0);
                else if (character == 'b')
                    color = rgb24(0, 0, 0x7f);
                else if (character == 'B')
                    color = rgb24(0, 0, 0xff);
                else if (character == 'r')
                    color = rgb24(0x7f, 0, 0);
                else if (character == 'R')
                    color = rgb24(0xff, 0, 0);                
                else if (character == 'y')
                    color = rgb24(0x7f, 0x7f, 0);
                else if (character == 'Y')
                    color = rgb24(0xff, 0xff, 0);
                else if (character == 'w')
                    color = rgb24(0x7f, 0x7f, 0x7f);
                else // if (character == 'W')
                    color = rgb24(0xff, 0xff, 0xff);

                escStatus = 0;
                continue;
            }

            escStatus=0;
        }

        if (!onlyMeasure)
            backgroundLayer.drawChar(x, y, color, character);
        x += curFont->Width;
    }
#endif
}

int Display_MeasureTextXLen(const char* text)
{
#ifdef DISPLAY_ENABLE
    int x=0;
    rgb24 color;

    Display_DrawTextX_Internal(x, 0, color, text, true);
    return x;
#else
    return 32;
#endif
}

void Display_DrawTextXCentered(int y, rgb24& startColor, const char* text)
{
#ifdef DISPLAY_ENABLE
    int x = 0;
    int dx = Display_MeasureTextXLen(text);
    if (dx < 64)
        x = (64 - dx) / 2;

    Display_DrawTextX_Internal(x, y, startColor, text, false);
#endif
}

void Display_DrawTextX(int x, int y, rgb24& startColor, const char* text)
{
#ifdef DISPLAY_ENABLE
    Display_DrawTextX_Internal(x, y, startColor, text, false);
#endif
}

void Display_DrawSubtitle(const char *subtitle, bool centered)
{
#ifdef DISPLAY_ENABLE
    rgb24 fullRed = rgb24(0xff, 0, 0);
    backgroundLayer.setFont(font5x7);

    if (centered)
        Display_DrawTextXCentered(22, fullRed, subtitle);
    else
        Display_DrawTextX(0, 22, fullRed, subtitle);
#endif
}

void Display_ShowImage(unsigned char *image)
{
#ifdef DISPLAY_ENABLE
    rgb24 fullRed = rgb24(0xff, 0, 0);
    rgb24 black = rgb24(0, 0, 0);

    backgroundLayer.fillScreen(black);
    for (int y=0; y<32; y++)
    {
        for (int x=0; x<64; x++)
        {
            unsigned char val = image[y*32 + x/2];            
            if (x%2 == 0)
                val >>= 4;
            else
                val &= 0xf;

            if (val != 0)
                backgroundLayer.drawPixel(x, y, fullRed);
        }
    }

    backgroundLayer.swapBuffers(false);
#endif
}
