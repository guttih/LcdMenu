#include "displaybutton.h"

DisplayButton::DisplayButton(TFT_eSPI *tft,
                             int16_t x,
                             int16_t y,
                             uint16_t width,
                             uint16_t height,
                             uint16_t outlineColor,
                             uint16_t fillColor,
                             uint16_t textColor,
                             uint8_t textsize, 
                             const char *text)
{

    init(tft, x, y, width, height, outlineColor, fillColor, textColor, textsize, text);
}

// Copy constructor
DisplayButton::DisplayButton(const DisplayButton &button)
{
    init(button._values.tft, button._values.x, button._values.y,
         button._values.width, button._values.height, button._values.outlineColor,
         button._values.fillColor, button._values.textColor,
         button._values.textsize, button._values.text.c_str());
}

void DisplayButton::serialPrintValues(unsigned int margin)
{
    for(int i = 0; i<margin; i++) 
        Serial.print(" "); 

    Serial.print("x:");              Serial.print(_values.x);
    Serial.print(", y:");            Serial.print(_values.y);
    Serial.print(", width:");        Serial.print(_values.width);
        Serial.print(", height:");   Serial.print(_values.height);
    Serial.print(", outlineColor:"); Serial.print(_values.outlineColor);   
    Serial.print(", fillColor:");    Serial.print(_values.fillColor, HEX); 
    Serial.print(", textColor:");    Serial.print(_values.textColor, HEX);
    Serial.print(", text:");         Serial.print(_values.text);
    Serial.print(", textsize:");     Serial.print(_values.textsize);
    Serial.print(", radius:");       Serial.print(_values.radius);
    Serial.print(",tft:");           Serial.print((unsigned long)_values.tft, HEX);
    Serial.println();
}

void DisplayButton::init(   TFT_eSPI *tft, 
                            int16_t x, 
                            int16_t y, 
                            uint16_t width,
                            uint16_t height,
                            uint16_t outlineColor,
                            uint16_t fillColor,
                            uint16_t textColor,
                            uint8_t textsize,
                            const char *text)
{

    _values.tft = tft;
    _values.x = x;
    _values.y = y;
    _values.width = width;
    _values.height = height;
    _values.outlineColor = outlineColor;
    _values.fillColor = fillColor;
    _values.textColor = textColor;
    _values.textsize = textsize;
    _values.text = text;

    //defaults
    _values.radius = min(width, height) / 6; // Corner radius
    _values.textDatum = MC_DATUM;
    _values.xDatumOffset = 0;
    _values.yDatumOffset = 0;
}

void DisplayButton::draw(bool inverted)
{

    uint16_t fillColor, outlineColor, textColor;
    if (!inverted)
    {
        fillColor = _values.fillColor;
        outlineColor = _values.outlineColor;
        textColor = _values.textColor;
    }
    else
    {
        fillColor = _values.textColor;
        outlineColor = _values.outlineColor;
        textColor = _values.fillColor;
    }

    _values.tft->fillRoundRect(_values.x, _values.y, _values.width, _values.height, _values.radius, fillColor);
    _values.tft->drawRoundRect(_values.x, _values.y, _values.width, _values.height, _values.radius, outlineColor);

    _values.tft->setTextColor(textColor);
    _values.tft->setTextSize(_values.textsize);

    
    uint8_t textDatumBefore = _values.tft->getTextDatum();
    uint8_t textPaddingBefore = _values.tft->getTextPadding();

    _values.tft->setTextDatum(_values.textDatum);
    _values.tft->setTextPadding(0);

    //_values.tft->drawString(_values.text, _values.x, _values.y);
    _values.tft->drawString(_values.text, _values.x + (_values.width/2) + _values.xDatumOffset, _values.y + (_values.height/2) - 4 + _values.yDatumOffset);

     _values.tft->setTextDatum(textDatumBefore);
     _values.tft->setTextPadding(textPaddingBefore);

}

bool DisplayButton::contains(int16_t x, int16_t y) {
  return ((x >= _values.x) && (x < (_values.x + _values.width)) &&
          (y >= _values.y) && (y < (_values.y + _values.height)));
}

void DisplayButton::press(bool isPressed) {
  _lastState = _currentState;
  _currentState = isPressed;
}

bool DisplayButton::isPressed()    { 
    return _currentState; 
}
bool DisplayButton::justPressed()  { 
    return (_currentState && !_lastState); 
}
bool DisplayButton::justReleased() { 
    return (!_currentState && _lastState); 
}