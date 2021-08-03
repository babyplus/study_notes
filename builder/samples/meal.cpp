#include "meal.h"

Meal::Meal()
{
    TRACK("begin");
}

Meal::~Meal()
{
    TRACK("end");
}

void Meal::add_item(Item* item)
{
    TRACK();
    items.push_back(item);
}

void Meal::show_items()
{
    TRACK();
}

int Meal::get_cost()
{
    TRACK();
    return 0;
}

