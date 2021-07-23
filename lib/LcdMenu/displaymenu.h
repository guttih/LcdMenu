#ifndef DISPLAYMENU_H
#define DISPLAYMENU_H

#include "arduino.h"
#include "FS.h"
#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library

#include "displaypage.h"
#include "displaypagelist.h"

struct TOUCHED_STRUCT {
    uint16_t x;
    uint16_t y;
    bool pressed;

};

class DisplayMenu
{
private:
    TFT_eSPI *_tft;
    int _visablePage;
    uint16_t _fillColor;  //default fill color for pages
    TOUCHED_STRUCT _touch;
    DisplayPageList pages;
    unsigned long myTouchTimer;
    unsigned long myTouchDelay;

    void init(TFT_eSPI *tft, uint16_t fillColor);
    
public:
    DisplayMenu(TFT_eSPI *tft, uint16_t fillColor = TFT_BLACK);
    DisplayPage * addPage();
    DisplayPage * addPage(uint16_t fillColor);
    DisplayPage * addPage(DisplayPage page);
    DisplayPage *getPage(int index);
    void drawPage(int index, bool wipeScreen=true);
    void drawPage(DisplayPage *pPage, bool wipeScreen=true);
    DisplayPage *getVisablePage();
    DisplayPage*  getLastPage();
    void update();
    
    
    //void drawButton(bool inverted, String long_name);

};


#endif