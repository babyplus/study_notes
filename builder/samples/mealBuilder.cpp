#include "mealBuilder.h"

MealBuilder::MealBuilder(Meal* meal)
{
    TRACK("begin");
    this->meal = meal;
}

MealBuilder::~MealBuilder()
{
    TRACK("end");
}

void MealBuilder::add(Item* item)
{
    meal->add_item(item);
}
