#ifndef DISPLAYBUTTON_H
#define DISPLAYBUTTON_H

#include "arduino.h"

#include "FS.h"

#include <SPI.h>

#include <TFT_eSPI.h>

class DisplayButton;

typedef void (*ButtonPressedFunction) (DisplayButton *ptr);

/**
 * @brief DisplayButton type enumeration which holds information on how the button behaves when it is pressed.
 * 
 */
enum DisplayButtonType {
    RUN_FUNCTION,
    OPEN_PAGE, 
    INCREMENT_VALUE
};

enum DisplayButtonState {
    VISABLE,
    HIDDEN
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
    bool allowOnlyOneButtonPressedAtATime;

    DisplayButtonType type;
    DisplayButtonState state;
    DisplayPage *pPage;
    double *pLinkedValue;
    String linkedValueName;
    double incrementValue;
    DisplayPage *pPageToOpen;
    ButtonPressedFunction buttonPressedFunction;
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
                DisplayButtonState state,
                DisplayPage *page,
                String linkedValueName,
                double *pLinkedValue,
                double incrementValue,
                DisplayPage *pageToOpen,
                ButtonPressedFunction buttonPressedFunction
                );
public:
    bool  _currentState, 
          _lastState; 
    String getText() { return _values.text; };
    void setText(String newText) { _values.text = newText; };
    void setLinkToValue(double *pLinkedValue, String valueName);
    
    double *getLinkedValue() { return _values.pLinkedValue; };
    String getLinkedValueName() { return _values.linkedValueName; };
    void setPageToOpen(DisplayPage *pageToOpen) { _values.pPageToOpen = pageToOpen; };
    DisplayPage *getPageToOpen() { return _values.pPageToOpen; };
    void setDatum(uint8_t textDatum, int16_t xDatumOffset, int16_t yDatumOffset) { _values.textDatum = textDatum; _values.xDatumOffset = xDatumOffset; _values.yDatumOffset = yDatumOffset; };
    void setState(DisplayButtonState state) { _values.state = state; };
    void show() { _values.state = DisplayButtonState::VISABLE; };
    void hide() { _values.state = DisplayButtonState::HIDDEN; };
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
                    DisplayPage *pPageToOpen,
                    ButtonPressedFunction buttonPressed
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
    void resetPressState();         
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