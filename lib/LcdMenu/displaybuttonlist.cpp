#include "displayButtonlist.h"
bool DisplayButtonList::add(DisplayButton button) {
    return LinkedList<DisplayButton*>::add(new DisplayButton(button));
}