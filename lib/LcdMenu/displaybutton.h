#ifndef DISPLAYBUTTON_H
#define DISPLAYBUTTON_H

#include "arduino.h"

#include "FS.h"

#include <SPI.h>

#include <TFT_eSPI.h>

/**
 * @brief DisplayButton type enumeration which holds information on how the button behaves when it is pressed.
 * 
 */
enum DisplayButtonType {
    OPEN_PAGE, 
    INCREMENT_VALUE
};

class DisplayPage;

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

    DisplayButtonType type;
    DisplayPage *pPage;
    double *pLinkedValue;
    double incrementValue;
    DisplayPage *pPageToOpen;
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
                const char *text,
                DisplayButtonType type,
                DisplayPage *page,
                double *pLinkedValue,
                double incrementValue,
                DisplayPage *pageToOpen
                );
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
                    const char *text,
                    DisplayButtonType type,
                    DisplayPage *page,
                    DisplayPage *pPageToOpen = NULL
                    );

    DisplayButton(  TFT_eSPI *tft,
                    int16_t x,
                    int16_t y,
                    uint16_t width,
                    uint16_t height,
                    uint16_t outlineColor,
                    uint16_t fillColor,
                    uint16_t textColor,
                    uint8_t textsize, 
                    const char *text,
                    DisplayButtonType type,
                    DisplayPage *page,
                    double *pLinkedValue,
                    double incrementValue
                );
                    
    void draw(bool inverted=false);
    bool contains(int16_t x, int16_t y);

    void serialPrintValues(unsigned int margin=0);

    void press(bool isPressed);
    bool isPressed();
    bool justPressed();
    bool justReleased();
    bool executeCommand();
    DisplayPage *getPage() { return _values.pPage; }
};


#endif