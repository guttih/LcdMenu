#ifndef DISPLAYPAGE_H
#define DISPLAYPAGE_H
#include "arduino.h"

#include "FS.h"

#include <SPI.h>

#include <TFT_eSPI.h> // Hardware-specific library

class DisplayPage
{
private:
    TFT_eSPI *_tft;
    void init(TFT_eSPI *tft);
public:
    /**
     * @brief Construct a new Display Page object (Copy constructor)
     * 
     * @param page 
     */
    DisplayPage(const DisplayPage &page);

    DisplayPage(TFT_eSPI *tft);
    /**
     * @brief draws all items on the page
     * 
     */
    void show();
};


#endif