#include "DisplayPage.h"

// Copy constructor
DisplayPage::DisplayPage(const DisplayPage &page)
{

    DisplayPage &ref = const_cast<DisplayPage &>(page);
    init(ref._tft, ref._pMenu, ref._fillColor);
    int buttonCount = ref.buttonCount();
    DisplayButton *pBtn;

    for (int i = 0; i < buttonCount; i++)
    {
        pBtn = ref.buttons.get(i);
        addButton(*pBtn);
    }
}

DisplayPage::DisplayPage(TFT_eSPI *tft, DisplayMenu *menu, uint16_t fillColor)
{
    init(tft, menu, fillColor);
}

void DisplayPage::init(TFT_eSPI *tft, DisplayMenu *menu, uint16_t fillColor)
{
    _tft = tft;
    _fillColor = fillColor;
    _customDrawFunction = NULL;
    _customShowFunction = NULL;
    _pMenu = menu;
}

// #define BLACK_SPOT

// // Switch position and size
// #define FRAME_X 100
// #define FRAME_Y 64
// #define FRAME_W 120
// #define FRAME_H 50

// // Red zone size
// #define REDBUTTON_X FRAME_X
// #define REDBUTTON_Y FRAME_Y
// #define REDBUTTON_W (FRAME_W / 2)
// #define REDBUTTON_H FRAME_H

// // Green zone size
// #define GREENBUTTON_X (REDBUTTON_X + REDBUTTON_W)
// #define GREENBUTTON_Y FRAME_Y
// #define GREENBUTTON_W (FRAME_W / 2)
// #define GREENBUTTON_H FRAME_H

bool DisplayPage::addButton(const DisplayButton button)
{
    return buttons.add(button);
}

bool DisplayPage::addPageButton(int16_t x, 
                            int16_t y, 
                            uint16_t width,
                            uint16_t height,
                            uint16_t outlineColor,
                            uint16_t fillColor,
                            uint16_t textColor,
                            uint8_t textsize, 
                            const char *text,
                            DisplayPage *pPageToOpen
                            )
{

    DisplayButton pageButton(getDisplay(), x, y, width, height, outlineColor, fillColor, textColor, textsize, text, DisplayButtonType::OPEN_PAGE, this, pPageToOpen, NULL);
    return buttons.add(pageButton);
}

bool DisplayPage::addFunctionButton(int16_t x, 
                            int16_t y, 
                            uint16_t width,
                            uint16_t height,
                            uint16_t outlineColor,
                            uint16_t fillColor,
                            uint16_t textColor,
                            uint8_t textsize, 
                            const char *text,
                            ButtonPressedFunction buttonPressedFunction
                            )
{

    DisplayButton functionButton(getDisplay(), x, y, width, height, outlineColor, fillColor, textColor, textsize, text, DisplayButtonType::RUN_FUNCTION, this, NULL, buttonPressedFunction);
    return buttons.add(functionButton);
}

bool DisplayPage::addIncrementButton(   int16_t x,
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
                ) 
{

    DisplayButton incrementButton(getDisplay(), x, y, width, height, outlineColor, fillColor, textColor, textsize, text, DisplayButtonType::INCREMENT_VALUE, this, pLinkedValue, incrementValue);
    return buttons.add(incrementButton);
}

void DisplayPage::serialPrintValues(unsigned int margin)
{

    int buttonCount = this->buttonCount();

    for (int x = 0; x < margin; x++) Serial.print(" ");

    Serial.print("_tft=");Serial.print((unsigned long)this->_tft, HEX);Serial.print(", ");
    Serial.print("buttonCount=");Serial.print(buttonCount);
    Serial.print(", ");Serial.println("buttons:");

    for (int i = 0; i < buttonCount; i++)
    {
        DisplayButton *btn = buttons.get(i);
        for (int x = 0; x < margin; x++) Serial.print(" ");
        Serial.print("    ");Serial.print(i); Serial.print(" -> ");
        Serial.print("address:"); Serial.print((unsigned long)btn, HEX); Serial.print(", ");
        btn->serialPrintValues();
    }
}

void DisplayPage::drawButtons()
{
    int buttonCount = this->buttonCount();
    for (int i = 0; i < buttonCount; i++)
    {
        DisplayButton *btn = buttons.get(i);
        btn->resetPressState();
        btn->draw();
    }
}

void DisplayPage::draw(bool wipeScreen) {
    
    if (wipeScreen)
        _tft->fillScreen(_fillColor);
    
    if (_customDrawFunction)
        _customDrawFunction(this);

    _tft->setFreeFont(&FreeMonoBold9pt7b); 
    drawButtons();
}

void DisplayPage::show() {
    
    if (_customShowFunction)
        _customShowFunction(this);

    draw(true);
}

DisplayButton *DisplayPage::getButton(int buttonIndex)
{
    return buttons.get(buttonIndex);
}

DisplayButton *DisplayPage::getPressedButton(uint16_t x, uint16_t y){
    
    int buttonCount = this->buttonCount();
    DisplayButton *pressedBtn = NULL;
    for (int i = buttonCount-1; i > -1; i--)
    {
        DisplayButton *btn = buttons.get(i);

        if (btn->contains(x, y)) {
            
             if (pressedBtn == NULL)
                pressedBtn = btn; //only return last button added
            btn->press(true);
        } 
        else {
            btn->press(false);
        }
    }
    return pressedBtn;
}

DisplayButton *DisplayPage::getLastButton()
{
    int size = buttons.size();
    if (size < 1)
        return NULL;

    return buttons.get(size - 1);
}

// todo:remove is this function needed???
void DisplayPage::drawButtonsState() { 

     int buttonCount = this->buttonCount();

    for (int i = 0; i < buttonCount; i++)
    {
         DisplayButton *btn = buttons.get(i);
         if (btn->justPressed()) 
            btn->draw(true);

        else if (btn->justReleased()) 
            btn->draw(false);
    }

}
