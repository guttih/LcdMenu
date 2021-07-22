#ifndef DISPLAYPAGE_H
#define DISPLAYPAGE_H
#include "arduino.h"

#include "FS.h"

#include <SPI.h>

#include <TFT_eSPI.h> // Hardware-specific library

#include "displaybutton.h"
#include "displaybuttonlist.h"


typedef void (*DisplayPageCustomDrawFunction) (void *ptr);
//typedef void (*DisplayPageCustomDrawFunction) (DisplayPage page); //todo:: hwo to make this compile

class DisplayPage
{
private:
    TFT_eSPI *_tft;
    uint16_t _fillColor;
    DisplayButtonList buttons;
    DisplayPageCustomDrawFunction _customDrawFunction;
    void init(TFT_eSPI *tft, uint16_t fillColor);
    bool addButton(const  DisplayButton button);

public:
    /**
     * @brief Construct a new Display Page object (Copy constructor)
     * 
     * @param page Page to copy values from to the new Constructed object.
     */
    DisplayPage(const DisplayPage &page);

    DisplayPage(TFT_eSPI *tft, uint16_t fillColor = TFT_BLACK);
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
    void draw(bool wipeScreen = true);

    int getPressedButtonIndex(uint16_t x, uint16_t y);
    void drawButtonsState();
    void serialPrintValues(unsigned int margin = 0);

    TFT_eSPI *getTft() { return _tft; };

    /**
     * @brief Provies a user defined function to  be called every time the page should be drawn.
     * 
     * @code .cpp
     * 
     * // When function draw() is called it will call this function and print out to serial most of the page values.
     * 
     * TFT_eSPI tft = TFT_eSPI();
     * void myCustomPageDrawFunc(void *ptrToPage)
     * {
     *     DisplayPage *pPage = (DisplayPage *)ptrToPage;
     *     pPage->serialPrintValues();
     * }
     * 
     * void ssetup()
     * {
     *     DisplayPage page1(&tft);
     *     page1.addCustomDrawFunction(myCustomPageDrawFunc);
     *     page1.addButton(100, 120, 136, 40, TFT_RED, TFT_PURPLE, TFT_WHITE, 1, "Hello world");
     *     page1.draw();
     * }
     * @endcode 
     * 
     * @param pCustomDrawFunction a pointer to a function which takes one void * parameter
     */
    void addCustomDrawFunction(DisplayPageCustomDrawFunction pCustomDrawFunction) {
        _customDrawFunction = pCustomDrawFunction;
    }
};


#endif