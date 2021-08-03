#ifndef __MEAL__
#define __MEAL__
#include <list>
#include "item.h"
#include "tracker.h"

class Meal
{
    public:
        Meal();
        virtual ~Meal();
        virtual void add_item(Item*);
        virtual void show_items();
        virtual int get_cost();
        
    private:
        std::list<Item*> items;
};
#endif
