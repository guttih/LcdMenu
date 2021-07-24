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
#include "getnumberpage.h"

const uint16_t TFT_BUTTON_OUTLINE = tft.color565(115, 149, 125);
const uint16_t TFT_BUTTON_FILL = tft.color565(48, 73, 47);
const uint16_t TFT_BUTTON_TEXT = TFT_GOLD;

void addPageMenu(){
    menu.addPage();
}



void pageValvesCustomDraw(DisplayPage *pPage) {
    
    //DisplayPage * pPage = (DisplayPage *)pagePtr;

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
    tft.drawRect(x,y, w, h, pPage->getFillColor());
    tft.fillRect(x,y, w, h, pPage->getFillColor());
    tft.drawString((String(values.coldValveFlow, 2))+"%", x, y);


    tft.setTextColor(tft.color24to16(0xfb745b));
    tft.drawString("Hot", 36+208, 40);

    x = 220, y  =70;
    tft.drawRect(x,y,w,h, pPage->getFillColor());
    tft.fillRect(x,y,w,h, pPage->getFillColor());
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
    
    addValve(pPage, false);
    addValve(pPage, true);
    

    
}

void print(DisplayButton *btn) {
    Serial.print("display button: ");Serial.println(btn->_values.text);
}

void setupMenu()
{
    addPageMenu();
    addPageValves();
    addPageEditValue(&menu, false);
    
    menu.getPage(1)->addPageButton((tft.width() - 100) /2, 0, 100, 50, tft.color565(115, 149, 125), tft.color565(48, 73, 47), TFT_GOLD, 1, "Menu",  menu.getPage(0));
    menu.getPage(1)->addFunctionButton((tft.width() - 100) /2, 50, 100, 50, tft.color565(115, 149, 125), tft.color565(48, 73, 47), TFT_GOLD, 1, "print", &print);

    //Add menu buttons
    const int buttonWidth = 170;
    const int buttonHeight = 50;
    const int buttonMargin = 20;
    const int x = (tft.width() - buttonWidth) /2;

    DisplayPage *pPage = menu.getPage(0);
    pPage->addPageButton(x, buttonMargin                                  , buttonWidth, buttonHeight, TFT_BUTTON_OUTLINE, TFT_BUTTON_FILL, TFT_BUTTON_TEXT, 1, "Valves",  menu.getPage(1));
    pPage->addPageButton(x, buttonMargin + 1 * (buttonMargin+buttonHeight), buttonWidth, buttonHeight, TFT_BUTTON_OUTLINE, TFT_BUTTON_FILL, TFT_BUTTON_TEXT, 1, "Edit global", menu.getPage(2));
    
    
    menu.showPage(0);
    //pPage->addPageButton(x, buttonMargin + 2 * (buttonMargin+buttonHeight), buttonWidth, buttonHeight, TFT_BUTTON_OUTLINE, TFT_BUTTON_FILL, TFT_BUTTON_TEXT, 1, "Button nr 3");
}

#endif