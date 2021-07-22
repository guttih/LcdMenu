/**
 * @file menusetup.h
 * @author guttih (gudjonholm@gmail.com)
 * @brief Global program functions for setting upp the menu and pages for the TFT display.
 * @date 2021-07-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MENUSETUPH
#define MENUSETUPH

#include <Arduino.h>
#include "globals.h"
#include "displaymenu.h"
#include "displaypage.h"
#include "displaybutton.h"

void setupMenu()
{
    DisplayPage *pPage = menu.addPage();
    if (!pPage)
    {
        Serial.println("Error adding page");
        return;
    }
    
    const int buttonWidth = 170;
    const int buttonHeight = 50;
    const int buttonMargin = 20;
    const int x = (tft.width() - buttonWidth) /2;
    const uint16_t TFT_BUTTON_OUTLINE = tft.color565(115, 149, 125);
    const uint16_t TFT_BUTTON_FILL = tft.color565(48, 73, 47);
    const uint16_t TFT_BUTTON_TEXT = TFT_GOLD;//tft.color24to16(0x00FFFF);

    pPage->addButton(x, buttonMargin, buttonWidth, buttonHeight, TFT_BUTTON_OUTLINE, TFT_BUTTON_FILL, TFT_BUTTON_TEXT, 1, "Button nr 1");
    pPage->addButton(x, buttonMargin+1 * (buttonMargin+buttonHeight), buttonWidth, buttonHeight, TFT_BUTTON_OUTLINE, TFT_BUTTON_FILL, TFT_BUTTON_TEXT, 1, "Button nr 2");
    pPage->addButton(x, buttonMargin+2 * (buttonMargin+buttonHeight), buttonWidth, buttonHeight, TFT_BUTTON_OUTLINE, TFT_BUTTON_FILL, TFT_BUTTON_TEXT, 1, "Button nr 3");
    
    menu.drawPage(0);
}

#endif