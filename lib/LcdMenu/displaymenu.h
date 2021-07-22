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
    uint16_t _fillColor;  //default fill color for pages
    TOUCHED_STRUCT _touch;
    int _visablePage;
    TFT_eSPI *_tft;
    DisplayPageList pages;
    void init(TFT_eSPI *tft, uint16_t fillColor);
public:
    DisplayMenu(TFT_eSPI *tft, uint16_t fillColor = TFT_BLACK);
    DisplayPage * addPage();
    DisplayPage * addPage(uint16_t fillColor);
    DisplayPage * addPage(DisplayPage page);
    DisplayPage *getPage(int index);
    void drawPage(int index, bool wipeScreen=true);
    DisplayPage *getVisablePage();
    DisplayPage*  getLastPage();
    void update();
    
    
    //void drawButton(bool inverted, String long_name);

};


#endif