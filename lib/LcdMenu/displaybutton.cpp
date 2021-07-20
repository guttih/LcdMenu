#include "displaybutton.h"

DisplayButton::DisplayButton(TFT_eSPI *tft) {
    init(tft);
}

// Copy constructor
DisplayButton::DisplayButton(const DisplayButton &button) {
  init(button._tft);
}

void DisplayButton::init(TFT_eSPI *tft) {
    _tft = tft;
}

void DisplayButton::draw() {
}
