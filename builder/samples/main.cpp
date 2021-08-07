#include "delete.h"
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
    DELETE(mb);
    DELETE(meal);
    DELETE(i0);
    DELETE(i1);
    return 0;
}
