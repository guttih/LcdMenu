#ifndef DISPLAYPAGE_H
#define DISPLAYPAGE_H
#include "arduino.h"

#include "FS.h"

#include <SPI.h>

#include <TFT_eSPI.h> // Hardware-specific library

#include "displaybutton.h"
#include "displaybuttonlist.h"

class DisplayMenu;


typedef void (*OnShowDisplayPage) (DisplayPage *pPage);
typedef void (*OnDrawDisplayPage) (DisplayPage *pPage);

class DisplayPage
{
private:
    TFT_eSPI *_tft;
    DisplayMenu *_pMenu;
    uint16_t _fillColor;
    DisplayButtonList buttons;
    OnShowDisplayPage _onShowDisplayPage;
    OnDrawDisplayPage _onDrawDisplayPage;
    void init(TFT_eSPI *tft, DisplayMenu *menu, uint16_t fillColor);
    bool addButton(const  DisplayButton button);

public:
    /**
     * @brief Construct a new Display Page object (Copy constructor)
     * 
     * @param page Page to copy values from to the new Constructed object.
     */
    DisplayPage(const DisplayPage &page);

    DisplayPage(TFT_eSPI *tft, DisplayMenu *menu, uint16_t fillColor = TFT_BLACK);
    /**
     * @brief draws all items on the page
     * 
     */
    TFT_eSPI *getDisplay() { return _tft; }

    /**
     * @brief Adds a new button which runs a function every time it is pressed
     * 
     * @param x Button upper left corner, x coordinate
     * @param y Button upper left corner, y coordinate
     * @param width Button width
     * @param height Button height
     * @param outlineColor Color of the line surrounding the button
     * @param fillColor Button color
     * @param textColor Button text color
     * @param textsize Button text multiplier size (2 is 100% bigger than normal).
     * @param text Button text
     * @param customDrawFunction 
     * @return true 
     * @return false 
     */
    bool addFunctionButton(int16_t x, 
                            int16_t y, 
                            uint16_t width,
                            uint16_t height,
                            uint16_t outlineColor,
                            uint16_t fillColor,
                            uint16_t textColor,
                            uint8_t textsize, 
                            const char *text,
                            ButtonPressedFunction buttonPressedFunction); 
    /**
     * @brief Adds a new button which opens a given page
     * 
     * @param x Button upper left corner, x coordinate
     * @param y Button upper left corner, y coordinate
     * @param width Button width
     * @param height Button height
     * @param outlineColor Color of the line surrounding the button
     * @param fillColor Button color
     * @param textColor Button text color
     * @param textsize Button text multiplier size (2 is 100% bigger than normal).
     * @param text Button text
     * @param pPageToOpen page the button belongs to
     * @return true if button was added
     * @return false if the button was NOT added to the page.
     */
    bool addPageButton( int16_t x, 
                    int16_t y, 
                    uint16_t width,
                    uint16_t height,
                    uint16_t outlineColor,
                    uint16_t fillColor,
                    uint16_t textColor,
                    uint8_t textsize, 
                    const char *text,
                    DisplayPage *pPageToOpen
                    );

    /**
     * @brief Adds a new increment button to the page
     * 
     * @param x Button upper left corner, x coordinate
     * @param y Button upper left corner, y coordinate
     * @param width Button width
     * @param height Button height
     * @param outlineColor Color of the line surrounding the button
     * @param fillColor Button color
     * @param textColor Button text color
     * @param textsize Button text multiplier size (2 is 100% bigger than normal).
     * @param text Button text
     * @param pLinkedValue value this button is suppose to change
     * @param incrementValue how munch should be value be incremented in each press
     * @return true if button was added
     * @return false if the button was NOT added to the page.
     */
    bool addIncrementButton(    int16_t x,
                                int16_t y,
                                uint16_t width,
                                uint16_t height,
                                uint16_t outlineColor,
                                uint16_t fillColor,
                                uint16_t textColor,
                                uint8_t textsize, 
                                const char *text,
                                double *pLinkedValue,
                                double incrementValue
                );

    /**
     * @brief Get a pointer to a specific button stored in the page.
     * 
     * @param buttonIndex Index of the button to get.
     * @return DisplayButton* 
     * @return if no button is found at the given index NULL is returned.
     */
    DisplayButton* getButton(int buttonIndex);

    /**
     * @brief Searches for a button by the button text
     * 
     * @param text 
     * @return DisplayButton* if a button was found, otherwise NULL
     */
    DisplayButton *getButtonByText(String text) { return buttons.findButtonByText(text); }

    int buttonCount() { return buttons.count(); } ;
    void drawButtons();
    void show();
    void draw(bool wipeScreen = true);

    DisplayButton *getPressedButton(uint16_t x, uint16_t y);
    void drawTouchButtonsState();
    void serialPrintValues(unsigned int margin = 0);

    TFT_eSPI *getTft() { return _tft; };
    
    DisplayMenu *getMenu() { return _pMenu; };
    uint16_t getFillColor() { return _fillColor; };

    DisplayButton * getLastButton();

    /**
     * @brief Provies a user defined function to  be called every time before the page should be drawn.
     * 
     * @code .cpp
     * 
     * When function draw() is called, it will call this function and print out to serial most of the page values.
     * 
     * TFT_eSPI tft = TFT_eSPI();
     * void myCustomPageDrawFunc(DisplayPage *pPage)
     * {
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
     * @param pOnDrawDisplayPage a pointer to a function which will be called just before the page is drawn
     */
    void registerOnDrawEvent(OnDrawDisplayPage pOnDrawDisplayPage) {
        _onDrawDisplayPage = pOnDrawDisplayPage;
    }

    /**
     * @brief Provies a user defined function to be called every time before the page should be shown.
     * 
     * @param pOnShowDisplayPage a pointer to a function which will be called just before the page is shown
     */
    void registerOnShowEvent(OnShowDisplayPage pOnShowDisplayPage) {
        _onShowDisplayPage = pOnShowDisplayPage;
    }

};


#endif