#include "DisplayPage.h"

DisplayPage::DisplayPage(TFT_eSPI *tft) {
    init(tft);
}

void DisplayPage::init(TFT_eSPI *tft) {
    _tft = tft;
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
#define REDBUTTON_W (FRAME_W/2)
#define REDBUTTON_H FRAME_H

// Green zone size
#define GREENBUTTON_X (REDBUTTON_X + REDBUTTON_W)
#define GREENBUTTON_Y FRAME_Y
#define GREENBUTTON_W (FRAME_W/2)
#define GREENBUTTON_H FRAME_H

void DisplayPage::show() {
  _tft->fillRect(REDBUTTON_X, REDBUTTON_Y, REDBUTTON_W, REDBUTTON_H, TFT_RED);
  _tft->fillRect(GREENBUTTON_X, GREENBUTTON_Y, GREENBUTTON_W, GREENBUTTON_H, TFT_DARKGREY);
  //drawFrame();
  _tft->setTextColor(TFT_WHITE);
  _tft->setTextSize(2);
  _tft->setTextDatum(MC_DATUM);
  _tft->drawString("ON", GREENBUTTON_X + (GREENBUTTON_W / 2), GREENBUTTON_Y + (GREENBUTTON_H / 2));
}

// Copy constructor
DisplayPage::DisplayPage(const DisplayPage &page) {
  init(page._tft);
}
