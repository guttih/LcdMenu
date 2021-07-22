#include "DisplayPage.h"

// Copy constructor
DisplayPage::DisplayPage(const DisplayPage &page)
{

    DisplayPage &ref = const_cast<DisplayPage &>(page);
    init(ref._tft, ref._fillColor);
    int buttonCount = ref.buttonCount();
    DisplayButton *pBtn;

    for (int i = 0; i < buttonCount; i++)
    {
        pBtn = ref.buttons.get(i);
        addButton(*pBtn);
    }
}

DisplayPage::DisplayPage(TFT_eSPI *tft, uint16_t fillColor)
{
    init(tft, fillColor);
}

void DisplayPage::init(TFT_eSPI *tft, uint16_t fillColor)
{
    _tft = tft;
    _fillColor = fillColor;
}

#define BLACK_SPOT

// Switch position and size
#define FRAME_X 100
#define FRAME_Y 64
#define FRAME_W 120
#define FRAME_H 50

// Red zone size
#define REDBUTTON_X FRAME_X
#define REDBUTTON_Y FRAME_Y
#define REDBUTTON_W (FRAME_W / 2)
#define REDBUTTON_H FRAME_H

// Green zone size
#define GREENBUTTON_X (REDBUTTON_X + REDBUTTON_W)
#define GREENBUTTON_Y FRAME_Y
#define GREENBUTTON_W (FRAME_W / 2)
#define GREENBUTTON_H FRAME_H

void DisplayPage::show()
{
    _tft->fillRect(REDBUTTON_X, REDBUTTON_Y, REDBUTTON_W, REDBUTTON_H, TFT_RED);
    _tft->fillRect(GREENBUTTON_X, GREENBUTTON_Y, GREENBUTTON_W, GREENBUTTON_H, TFT_DARKGREY);
    //drawFrame();
    _tft->setTextColor(TFT_WHITE);
    _tft->setTextSize(2);
    _tft->setTextDatum(MC_DATUM);
    _tft->drawString("ON", GREENBUTTON_X + (GREENBUTTON_W / 2), GREENBUTTON_Y + (GREENBUTTON_H / 2));
}

bool DisplayPage::addButton(const DisplayButton button)
{
    return buttons.add(button);
}

bool DisplayPage::addButton(int16_t x, 
                            int16_t y, 
                            uint16_t width,
                            uint16_t height,
                            uint16_t outlineColor,
                            uint16_t fillColor,
                            uint16_t textColor,
                            uint8_t textsize, 
                            const char *text)
{

    DisplayButton btnToAdd(getDisplay(), x, y, width, height, outlineColor, fillColor, textColor, textsize, text);
    return buttons.add(btnToAdd);
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
        btn->draw();
    }
}

void DisplayPage::draw() {
    serialPrintValues();
    _tft->fillScreen(_fillColor);
    drawButtons();
}

DisplayButton *DisplayPage::getButton(int buttonIndex)
{
    return buttons.get(buttonIndex);
}

int DisplayPage::getPressedButtonIndex(uint16_t x, uint16_t y){
    
    int buttonCount = this->buttonCount();
    int index = -1;
    for (int i = buttonCount-1; i > -1; i--)
    {
        DisplayButton *btn = buttons.get(i);

        if (btn->contains(x, y) && index == -1) {
            //checking index == -1 to allow only last button added to be pressed
            index = i;
            btn->press(true);
        } 
        else {
            btn->press(false);
        }

        //todo: should this been done in drawButtonsState?  This is faster but does that matter?
        if (btn->justPressed())
            btn->draw(true);
        else if (btn->justReleased())
            btn->draw(false);
    }
    return index;
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
