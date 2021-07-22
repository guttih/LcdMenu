#ifndef DISPLAYBUTTON_H
#define DISPLAYBUTTON_H

#include "arduino.h"

#include "FS.h"

#include <SPI.h>

#include <TFT_eSPI.h>

/**
 * @brief DisplayButton type Enumeration which holds information on what type of button it is.
 * 
 */
enum DisplayButtonType {
    NORMAL, 
    INCREMENT
};

struct DISPLAY_BUTTON_VALUES {
    TFT_eSPI *tft;
    int16_t x;
    int16_t y; 
    int16_t xDatumOffset;
    int16_t yDatumOffset;
    uint16_t width;
    uint16_t height;
    uint16_t outlineColor;
    uint16_t fillColor;
    uint16_t textColor;
    uint8_t textsize;
    uint8_t textDatum;
    uint8_t radius;

    String text;
}; 

class DisplayButton
{
private:
    double _dTemp;
    void init(  TFT_eSPI *tft, 
                int16_t x, 
                int16_t y, 
                uint16_t width,
                uint16_t height,
                uint16_t outlineColor,
                uint16_t fillColor,
                uint16_t textColor,
                uint8_t textsize,
                const char *text);
public:
    bool  _currentState, 
          _lastState; 

    DISPLAY_BUTTON_VALUES _values;
    DISPLAY_BUTTON_VALUES getValues() { return _values; };

    DisplayButton(const DisplayButton &button);
    
    DisplayButton(  TFT_eSPI *tft, 
                    int16_t x, 
                    int16_t y, 
                    uint16_t width,
                    uint16_t height,
                    uint16_t outlineColor,
                    uint16_t fillColor,
                    uint16_t textColor,
                    uint8_t textsize,
                    const char *text
                    );
                    
    void draw(bool inverted=false);
    bool contains(int16_t x, int16_t y);

    void serialPrintValues(unsigned int margin=0);

    void press(bool isPressed);
    bool isPressed();
    bool justPressed();
    bool justReleased();
    
};


#endif