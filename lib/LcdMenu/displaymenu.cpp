#include "displaymenu.h"

DisplayMenu::DisplayMenu(TFT_eSPI *tft) {
    init(tft);
}

void DisplayMenu::init(TFT_eSPI *tft) {
    _tft = tft;

    _tft->init();
    // // Set the rotation before we calibrate
    _tft->setRotation(1);
    // // Clear screen
    _tft->fillScreen(TFT_BLACK);

    _tft->setFreeFont(&FreeMono9pt7b);

}

void DisplayMenu::showPage(unsigned int index) {
  DisplayPage page(_tft);
  page.show();
}

unsigned int DisplayMenu::addPage(DisplayPage page) {
  
}
