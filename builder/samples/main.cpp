#include "meal.h"
#include "mealBuilder.h"
#include "hamburg.h"
#include "cala.h"

int main()
{
    Meal* meal = new Meal();
    MealBuilder* mb = new MealBuilder(meal);
    Item* i0 = new Hamburg();
    Item* i1 = new Cala();
    mb->add(i0);
    mb->add(i1);
    delete mb;
    delete meal;
    delete i0;
    delete i1;
    return 0;
}
