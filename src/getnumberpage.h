/**
 * @file getnumberpage.h
 * @author guttih (gudjonholm@gmail.com)
 * @brief Creates a page that can modify a number
 * @version 0.1
 * @date 2021-07-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef GETNUMBERPAGEH
#define GETNUMBERPAGEH

#include "displaymenu.h"

double globalValue = 123.5;

//want full precision but no ending zeros and no ending dot
String removeUnNecessaryDoubleEnding(String str){
    
    if (str.indexOf('.') > -1)
    {
        int len = str.length();
        while (len > 1 && (str.charAt(len - 1) == '0'))
        {
            str.remove(len - 1, 1);
            len = str.length();
        }
    }

    if (str.endsWith("."))
        str.remove(str.length() - 1, 1);

    return str;
}

String toString(double num) {
    char output[50];

    snprintf(output, 50, "%.9f", num);
    return removeUnNecessaryDoubleEnding(output);
}

/**
 * @brief checks and converts a string to a double double
 * 
 * @param str a string to be tested and remove un necessary endings like 0 and .
 * @return String if success a string which can be converted to double and if fail an empty string:
 */
String convertToDoubleAndBackToSameString(String str)
{
    double d = str.toDouble();
    int dotPos = str.indexOf('.');
    int fractionLength = dotPos < 0? 0: str.length() - (dotPos + 1);
    String diffString = String(d,fractionLength);

    diffString = removeUnNecessaryDoubleEnding(diffString);

    if (diffString.equals(removeUnNecessaryDoubleEnding(str)))
        return diffString;
    else
        return "";
}

void pageEditCustomShow (DisplayPage *pPage) {
    DisplayButton *btnValue = pPage->getLastButton();

    if (btnValue->getLinkedValue()){
        btnValue->setText(toString(*btnValue->getLinkedValue()));
    }

}

void pageEditCustomDraw (DisplayPage *pPage) {
    DisplayButton *btnValue = pPage->getLastButton();

    pPage->getDisplay()->drawString(btnValue->_values.linkedValueName, 12, 44);

    btnValue->draw();

}

void pageEditKeyPressed(DisplayButton *btn)
{
    DisplayPage *pPage = btn->getPage();

    char firstChar = 'x';

    if (btn->getText().length() > 0)
        firstChar = btn->_values.text.charAt(0);
    else
        return; //bad text on button

    DisplayButton *valueButton = btn->getPage()->getLastButton();
    String currentValue = valueButton->getText();
    String newStr = "";
    int currentLength = currentValue.length();
    switch (firstChar)
    {

    case 'O': //OK
        if (valueButton->getLinkedValue())
        {
             newStr = convertToDoubleAndBackToSameString(currentValue);
            double newVal = newStr.toDouble();
            *(valueButton->getLinkedValue()) = newVal;
        }

        pPage->getMenu()->showPage(valueButton->getPageToOpen());
        return;
        break;

    case 'C': //Cancel
        pPage->getMenu()->showPage(valueButton->getPageToOpen());
        return;
        break;

    case 'R': //Reset
            valueButton->setText("0");
        break;

    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        if (currentValue == "0")
        {
            valueButton->setText(String(firstChar));
        }
        else
        {
            newStr = convertToDoubleAndBackToSameString(currentValue + firstChar);

            if (newStr.length() > 0)
                valueButton->setText(currentValue + firstChar);
        }
        break;

    case '.':
        if (currentValue.indexOf('.') < 0)
        {
            if (currentLength < 0)
                currentValue = '0';

            valueButton->setText(currentValue + firstChar);
        }
        break;

    case 'D': //delete

        if (currentLength > 1)
        {   
            currentValue.remove(currentLength - 1, 1);
            valueButton->setText(currentValue);
        }
        else
        {
            valueButton->setText("0");
        }
        break;
    }

    pageEditCustomDraw(pPage);
}

void addPageEditValue(DisplayMenu *pMenu, bool allowDouble)
{
    DisplayPage *pPage = pMenu->addPage();

    const int keyRows = 4;
    const int keyCols = 3;

    const int keyCount = (keyRows * keyCols) - 1;
    // char keys[keyRows][keyCols][2] = {
    //     { "7",  "8",  "9" },
    //     { "4",  "5",  "6" },
    //     { "1",  "2",  "3" },
    //     { "0",  ".",  "x" }
    // };

    char keys[keyCount][2] = {
        "7", "8", "9",
        "4", "5", "6",
        "1", "2", "3",
        "0", "."};

    struct COMMAND_BUTTON {
        char text[3];
        uint16_t fillColor;
    };

    Serial.println();

    const uint16_t TFT_BUTTON_OUTLINE = tft.color565(115, 149, 125);
    const uint16_t TFT_BUTTON_FILL = tft.color565(48, 73, 47);
    const uint16_t TFT_BUTTON_TEXT = TFT_GOLD;

    int buttonWidth = 50;
    const int buttonHeight = 39;
    int buttonMarginX = 10;
    const int buttonMarginY = 68;
    const int buttonPaddingX = 5;
    const int buttonPaddingY = 5;
    

    int col, row = 0;
    for (int x = 0; x < keyCount; x++)
    {
        col = x % 3;
        if (x != keyCount-1 || allowDouble )
        pPage->addFunctionButton(buttonMarginX + (col * (buttonPaddingX + buttonWidth)), buttonMarginY + (row * (buttonHeight + buttonPaddingY)),
                                 buttonWidth, buttonHeight,
                                 TFT_BUTTON_OUTLINE, TFT_BUTTON_FILL, TFT_BUTTON_TEXT, 1, keys[x], pageEditKeyPressed);
        if ((x + 1) % 3 == 0)
            row++;

    }

    buttonWidth = 130;
    buttonMarginX = 180;
    pPage->addFunctionButton(buttonMarginX, buttonMarginY                                        , buttonWidth, buttonHeight, TFT_BUTTON_OUTLINE, TFT_BROWN      , TFT_BUTTON_TEXT, 1,"Delete", pageEditKeyPressed);
    pPage->addFunctionButton(buttonMarginX, buttonMarginY + (1 * (buttonHeight + buttonPaddingY)), buttonWidth, buttonHeight, TFT_BUTTON_OUTLINE, TFT_BROWN     , TFT_BUTTON_TEXT, 1,"Reset",   pageEditKeyPressed);
   
    pPage->addFunctionButton(buttonMarginX, buttonMarginY + (2 * (buttonHeight + buttonPaddingY)), buttonWidth, buttonHeight, TFT_BUTTON_OUTLINE, TFT_DARKGREEN  , TFT_BUTTON_TEXT, 1,"OK"    , pageEditKeyPressed);
    pPage->addFunctionButton(buttonMarginX, buttonMarginY + (3 * (buttonHeight + buttonPaddingY)), buttonWidth, buttonHeight, TFT_BUTTON_OUTLINE, TFT_RED        , TFT_BUTTON_TEXT, 1,"Cancel", pageEditKeyPressed);

    pPage->addFunctionButton(10, 1, 300, buttonHeight, TFT_BUTTON_OUTLINE , pPage->getDisplay()->color565(25, 25, 25), TFT_BUTTON_TEXT, 1, String(globalValue).c_str(), NULL);
    
    
    DisplayButton *btn = pPage->getLastButton();
    btn->setPageToOpen(pPage->getMenu()->getPage(0));
    btn->linkToValue(&globalValue, "Global value");
    btn->setDatum(MR_DATUM, 140,3);
    btn->serialPrintValues();
    
    pPage->addCustomDrawFunction(pageEditCustomDraw);
    pPage->addCustomShowFunction(pageEditCustomShow);
    

    
}
#endif