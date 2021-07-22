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

    pPage->addButton(x, buttonMargin, buttonWidth, buttonHeight, TFT_BUTTON_OUTLINE, TFT_BUTTON_FILL, TFT_BUTTON_TEXT, 1, "Button nr 1");
    pPage->addButton(x, buttonMargin+1 * (buttonMargin+buttonHeight), buttonWidth, buttonHeight, TFT_BUTTON_OUTLINE, TFT_BUTTON_FILL, TFT_BUTTON_TEXT, 1, "Button nr 2");
    pPage->addButton(x, buttonMargin+2 * (buttonMargin+buttonHeight), buttonWidth, buttonHeight, TFT_BUTTON_OUTLINE, TFT_BUTTON_FILL, TFT_BUTTON_TEXT, 1, "Button nr 3");
    
    
}

void pageValvesCustomDraw(void *pagePtr) {
    DisplayPage *pPage = (DisplayPage*)pagePtr;
    
    DisplayPage page(&tft);
    int16_t screenXCenter = tft.width()/2;

    tft.setFreeFont(&FreeSans12pt7b);

    tft.setTextColor(TFT_CYAN);
    tft.drawString("Cold", 36, 40);
    tft.drawString("78.4%", 35, 70);

    tft.setTextColor(tft.color24to16(0xfb745b));
    tft.drawString("Hot", 36+208, 40);
    tft.drawString("12.7%", 35+200, 70);

    tft.setTextColor(TFT_GOLD);
    
    tft.setTextDatum(C_BASELINE);
    tft.drawString("24.87°", screenXCenter, 220);
    
    tft.setFreeFont(&FreeSans9pt7b);
    tft.drawString("Temperature", screenXCenter, 200);
    //tft.drawString("Temperature", 10+100, 160);
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
    int count = -1;
    pPage->addButton( buttonMarginX + ((++count % 2) * (buttonPaddingX + buttonWidth) ) + x, buttonMarginY+ (count % 3) * (buttonHeight + buttonPaddingY), buttonWidth, buttonHeight, TFT_BUTTON_OUTLINE, TFT_BUTTON_FILL, TFT_BUTTON_TEXT, 1, "<");
    pPage->addButton( buttonMarginX + ((++count % 2) * (buttonPaddingX + buttonWidth) ) + x, buttonMarginY+ (count % 3) * (buttonHeight + buttonPaddingY), buttonWidth, buttonHeight, TFT_BUTTON_OUTLINE, TFT_BUTTON_FILL, TFT_BUTTON_TEXT, 1, ">>");
    pPage->addButton( buttonMarginX + ((++count % 2) * (buttonPaddingX + buttonWidth) ) + x, buttonMarginY+ (count % 3) * (buttonHeight + buttonPaddingY), buttonWidth, buttonHeight, TFT_BUTTON_OUTLINE, TFT_BUTTON_FILL, TFT_BUTTON_TEXT, 1, "<<<");
    pPage->addButton( buttonMarginX + ((++count % 2) * (buttonPaddingX + buttonWidth) ) + x, buttonMarginY+ (count % 3) * (buttonHeight + buttonPaddingY), buttonWidth, buttonHeight, TFT_BUTTON_OUTLINE, TFT_BUTTON_FILL, TFT_BUTTON_TEXT, 1, ">");
    pPage->addButton( buttonMarginX + ((++count % 2) * (buttonPaddingX + buttonWidth) ) + x, buttonMarginY+ (count % 3) * (buttonHeight + buttonPaddingY), buttonWidth, buttonHeight, TFT_BUTTON_OUTLINE, TFT_BUTTON_FILL, TFT_BUTTON_TEXT, 1, "<<");
    pPage->addButton( buttonMarginX + ((++count % 2) * (buttonPaddingX + buttonWidth) ) + x, buttonMarginY+ (count % 3) * (buttonHeight + buttonPaddingY), buttonWidth, buttonHeight, TFT_BUTTON_OUTLINE, TFT_BUTTON_FILL, TFT_BUTTON_TEXT, 1, ">>>");
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
    // const int buttonWidth = 42;
    // const int buttonHeight = 39;
    // const int buttonMarginX = 10;
    // const int buttonMarginY = 100;
    // const int buttonPaddingX = 3;
    // const int buttonPaddingY = 3;
    // const int x = 10;
    // const uint16_t TFT_BUTTON_OUTLINE = tft.color565(115, 149, 125);
    // const uint16_t TFT_BUTTON_FILL = tft.color565(48, 73, 47);
    // const uint16_t TFT_BUTTON_TEXT = TFT_GOLD;//tft.color24to16(0x00FFFF);
    // int count = -1;
    // pPage->addButton( buttonMarginX + ((++count % 2) * (buttonPaddingX + buttonWidth) ) + x, buttonMarginY+ (count % 3) * (buttonHeight + buttonPaddingY), buttonWidth, buttonHeight, TFT_BUTTON_OUTLINE, TFT_BUTTON_FILL, TFT_BUTTON_TEXT, 1, "<");
    // pPage->addButton( buttonMarginX + ((++count % 2) * (buttonPaddingX + buttonWidth) ) + x, buttonMarginY+ (count % 3) * (buttonHeight + buttonPaddingY), buttonWidth, buttonHeight, TFT_BUTTON_OUTLINE, TFT_BUTTON_FILL, TFT_BUTTON_TEXT, 1, ">>");
    // pPage->addButton( buttonMarginX + ((++count % 2) * (buttonPaddingX + buttonWidth) ) + x, buttonMarginY+ (count % 3) * (buttonHeight + buttonPaddingY), buttonWidth, buttonHeight, TFT_BUTTON_OUTLINE, TFT_BUTTON_FILL, TFT_BUTTON_TEXT, 1, "<<<");
    // pPage->addButton( buttonMarginX + ((++count % 2) * (buttonPaddingX + buttonWidth) ) + x, buttonMarginY+ (count % 3) * (buttonHeight + buttonPaddingY), buttonWidth, buttonHeight, TFT_BUTTON_OUTLINE, TFT_BUTTON_FILL, TFT_BUTTON_TEXT, 1, ">");
    // pPage->addButton( buttonMarginX + ((++count % 2) * (buttonPaddingX + buttonWidth) ) + x, buttonMarginY+ (count % 3) * (buttonHeight + buttonPaddingY), buttonWidth, buttonHeight, TFT_BUTTON_OUTLINE, TFT_BUTTON_FILL, TFT_BUTTON_TEXT, 1, "<<");
    // pPage->addButton( buttonMarginX + ((++count % 2) * (buttonPaddingX + buttonWidth) ) + x, buttonMarginY+ (count % 3) * (buttonHeight + buttonPaddingY), buttonWidth, buttonHeight, TFT_BUTTON_OUTLINE, TFT_BUTTON_FILL, TFT_BUTTON_TEXT, 1, ">>>");
    
}

void setupMenu()
{
    addPageMenu();
    addPageValves();
    menu.drawPage(1);
}

#endif