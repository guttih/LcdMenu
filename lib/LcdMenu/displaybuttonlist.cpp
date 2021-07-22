#include "displayButtonlist.h"
bool DisplayButtonList::add(DisplayButton button) {
    return LinkedList<DisplayButton*>::add(new DisplayButton(button));
}

void DisplayButtonList::destory() {
    DisplayButton* p;
    for (int i = 0; i < size(); i++) {
        p = get(i);
        if (p != NULL)
        {
            delay(10);
            delete p;
            set(i, NULL);
        }
    }
    clear();
}