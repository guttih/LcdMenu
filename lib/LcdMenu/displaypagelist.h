#ifndef DISPLAYPAGELIST_H
#define DISPLAYPAGELIST_H


#include "linkedlist.h"
#include "displaypage.h"

class DisplayPageList : public LinkedList<DisplayPage*> {

private:
    
    /**
     * @brief The cleanup function used by the list's deconstructor;
     * 
     */
    void destory();

public:
    bool add(DisplayPage page);
    
};

#endif