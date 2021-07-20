#include "displaypagelist.h"
bool DisplayPageList::add(DisplayPage page) {
    return LinkedList<DisplayPage*>::add(new DisplayPage(page));
}