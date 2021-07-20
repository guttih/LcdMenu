#ifndef DISPLAYMENU_H
#define DISPLAYMENU_H

#include "arduino.h"
#include "FS.h"
#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library

#include "displaypage.h"

class DisplayMenu
{
private:
    TFT_eSPI *_tft;
    void init(TFT_eSPI *tft);
public:
    DisplayMenu(TFT_eSPI *tft);
    void showPage(unsigned int index);
    unsigned int addPage(DisplayPage page);
    //void drawButton(bool inverted, String long_name);

};


#endif