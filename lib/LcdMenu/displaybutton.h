#ifndef DISPLAYBUTTON_H
#define DISPLAYBUTTON_H
#include "arduino.h"

#include "FS.h"

#include <SPI.h>

#include <TFT_eSPI.h> // Hardware-specific library

class DisplayButton
{
private:
    TFT_eSPI *_tft;
    void init(TFT_eSPI *tft);
public:
    DisplayButton(const DisplayButton &button);
    DisplayButton(TFT_eSPI *tft);
    void draw();
    //void drawButton(bool inverted, String long_name);

};


#endif