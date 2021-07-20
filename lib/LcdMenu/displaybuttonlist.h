#ifndef DISPLAYBUTTONLIST_H
#define DISPLAYBUTTONLIST_H


#include "linkedlist.h"
#include "displaybutton.h"

class DisplayButtonList : public LinkedList<DisplayButton*> {

private:
    
    /**
     * @brief The cleanup function used by the list's deconstructor;
     * 
     */
    void destory();

public:
    bool add(DisplayButton page);
    
};

#endif