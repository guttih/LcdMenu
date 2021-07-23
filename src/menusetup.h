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

void addPageMenu(){
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

    pPage->addPageButton(x, buttonMargin, buttonWidth, buttonHeight, TFT_BUTTON_OUTLINE, TFT_BUTTON_FILL, TFT_BUTTON_TEXT, 1, "Valves",  menu.getPage(0));
    //pPage->addButton(x, buttonMargin+1 * (buttonMargin+buttonHeight), buttonWidth, buttonHeight, TFT_BUTTON_OUTLINE, TFT_BUTTON_FILL, TFT_BUTTON_TEXT, 1, "Button nr 2");
    //pPage->addButton(x, buttonMargin+2 * (buttonMargin+buttonHeight), buttonWidth, buttonHeight, TFT_BUTTON_OUTLINE, TFT_BUTTON_FILL, TFT_BUTTON_TEXT, 1, "Button nr 3");
}

void pageValvesCustomDraw(void *pagePtr) {
    
    DisplayPage * pPage = (DisplayPage *)pagePtr;

    if (values.coldValveFlow < 0) values.coldValveFlow = 0;
    if (values.coldValveFlow > 100) values.coldValveFlow = 100;
    if (values.hotValveFlow < 0) values.hotValveFlow = 0;
    if (values.hotValveFlow > 100) values.hotValveFlow = 100;
    tft.setFreeFont(&FreeSans12pt7b);

    int16_t screenXCenter = tft.width()/2;

    tft.setTextDatum(TL_DATUM);

    tft.setTextColor(TFT_CYAN);
    tft.drawString("Cold", 36, 40);

    int32_t h=20, w=100, x = 20, y  =70;
    tft.fillRect(x,y, w, h, pPage->getFillColor());
    tft.drawString((String(values.coldValveFlow, 2))+"%", x, y);

    
    tft.setTextColor(tft.color24to16(0xfb745b));
    tft.drawString("Hot", 36+208, 40);

    x = 220, y  =70;
    tft.fillRect(x, y, w, h, pPage->getFillColor());
    tft.drawString((String(values.hotValveFlow, 2))+"%", x, y);

    tft.setTextColor(TFT_GOLD);
    tft.setTextDatum(C_BASELINE);
    tft.drawString("24.87°", screenXCenter, 220);
    
    tft.setFreeFont(&FreeSans9pt7b);
    tft.drawString("Temperature", screenXCenter, 200);

}

void addValve(DisplayPage *pPage, bool hotValve) {
    const int buttonWidth = 42;
    const int buttonHeight = 39;
    const int buttonMarginX = 10;
    const int buttonMarginY = 100;
    const int buttonPaddingX = 3;
    const int buttonPaddingY = 3;
    const int x = hotValve? 208 : 5;
    const uint16_t TFT_BUTTON_OUTLINE = tft.color565(115, 149, 125);
    const uint16_t TFT_BUTTON_FILL = tft.color565(48, 73, 47);
    const uint16_t TFT_BUTTON_TEXT = TFT_GOLD;//tft.color24to16(0x00FFFF);
    double *pPlowValue = hotValve? &values.hotValveFlow : &values.coldValveFlow;
    

    int btnCount = -1;
    ++btnCount; pPage->addIncrementButton( buttonMarginX + ((btnCount % 2) * (buttonPaddingX + buttonWidth) ) + x, buttonMarginY+ (btnCount % 3) * (buttonHeight + buttonPaddingY), buttonWidth, buttonHeight, TFT_BUTTON_OUTLINE, TFT_BUTTON_FILL, TFT_BUTTON_TEXT, 1, "<"  , pPlowValue, -0.1);
    ++btnCount; pPage->addIncrementButton( buttonMarginX + ((btnCount % 2) * (buttonPaddingX + buttonWidth) ) + x, buttonMarginY+ (btnCount % 3) * (buttonHeight + buttonPaddingY), buttonWidth, buttonHeight, TFT_BUTTON_OUTLINE, TFT_BUTTON_FILL, TFT_BUTTON_TEXT, 1, ">>" , pPlowValue, 1);
    ++btnCount; pPage->addIncrementButton( buttonMarginX + ((btnCount % 2) * (buttonPaddingX + buttonWidth) ) + x, buttonMarginY+ (btnCount % 3) * (buttonHeight + buttonPaddingY), buttonWidth, buttonHeight, TFT_BUTTON_OUTLINE, TFT_BUTTON_FILL, TFT_BUTTON_TEXT, 1, "<<<", pPlowValue, -10);
    ++btnCount; pPage->addIncrementButton( buttonMarginX + ((btnCount % 2) * (buttonPaddingX + buttonWidth) ) + x, buttonMarginY+ (btnCount % 3) * (buttonHeight + buttonPaddingY), buttonWidth, buttonHeight, TFT_BUTTON_OUTLINE, TFT_BUTTON_FILL, TFT_BUTTON_TEXT, 1, ">"  , pPlowValue, 0.1);
    ++btnCount; pPage->addIncrementButton( buttonMarginX + ((btnCount % 2) * (buttonPaddingX + buttonWidth) ) + x, buttonMarginY+ (btnCount % 3) * (buttonHeight + buttonPaddingY), buttonWidth, buttonHeight, TFT_BUTTON_OUTLINE, TFT_BUTTON_FILL, TFT_BUTTON_TEXT, 1, "<<" , pPlowValue, -1);
    ++btnCount; pPage->addIncrementButton( buttonMarginX + ((btnCount % 2) * (buttonPaddingX + buttonWidth) ) + x, buttonMarginY+ (btnCount % 3) * (buttonHeight + buttonPaddingY), buttonWidth, buttonHeight, TFT_BUTTON_OUTLINE, TFT_BUTTON_FILL, TFT_BUTTON_TEXT, 1, ">>>", pPlowValue, 10);
}

void addPageValves(){
    DisplayPage *pPage = menu.addPage();
    pPage->addCustomDrawFunction(pageValvesCustomDraw);
    if (!pPage)
    {
        Serial.println("Error adding page");
        return;
    }
    
    addValve(pPage, false);
    addValve(pPage, true);
}

void setupMenu()
{
    addPageValves();
    addPageMenu();
    menu.drawPage(1);
}

#endif