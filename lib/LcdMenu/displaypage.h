#ifndef DISPLAYPAGE_H
#define DISPLAYPAGE_H
#include "arduino.h"

#include "FS.h"

#include <SPI.h>

#include <TFT_eSPI.h> // Hardware-specific library

#include "displaybutton.h"
#include "displaybuttonlist.h"

class DisplayPage
{
private:
    TFT_eSPI *_tft;
    uint16_t _fillColor;

    DisplayButtonList buttons;
    void init(TFT_eSPI *tft, uint16_t fillColor);
    bool addButton(const  DisplayButton button);

public:
    /**
     * @brief Construct a new Display Page object (Copy constructor)
     * 
     * @param page Page to copy values from to the new Constructed object.
     */
    DisplayPage(const DisplayPage &page);

    DisplayPage(TFT_eSPI *tft, uint16_t fillColor);
    /**
     * @brief draws all items on the page
     * 
     */
    void show();
    TFT_eSPI *getDisplay() { return _tft; }

    /**
     * @brief Adds a new button to the page
     * 
     * @param x Button upper left corner, x coordinate
     * @param y Button upper left corner, y coordinate
     * @param width Button width
     * @param height Button height
     * @param outlineColor Color of the line surrounding the button
     * @param fillColor Button color
     * @param textColor Button text color
     * @param caption Button text
     * @param textsize Button text multiplier size (1.1 is 10% bigger than normal).
     * @return true if button was added
     * @return false if the button was NOT added to the page.
     */
    bool addButton( int16_t x, 
                    int16_t y, 
                    uint16_t width,
                    uint16_t height,
                    uint16_t outlineColor,
                    uint16_t fillColor,
                    uint16_t textColor,
                    uint8_t textsize, 
                    const char *text);
    

    /**
     * @brief Get a pointer to a specific button stored in the page.
     * 
     * @param buttonIndex Index of the button to get.
     * @return DisplayButton* 
     * @return if no button is found at the given index NULL is returned.
     */
    DisplayButton* getButton(int buttonIndex);

    int buttonCount() { return buttons.count(); } ;
    void drawButtons();
    void draw();

    int getPressedButtonIndex(uint16_t x, uint16_t y);
    void drawButtonsState();

    void serialPrintValues(unsigned int margin = 0);
};


#endif