#include "tracker.h"
#include "meal.h"
#include "item.h"

class MealBuilder
{
    public:
        MealBuilder(Meal*);
        virtual ~MealBuilder();
        virtual void add(Item*);
        
    private:
        Meal* meal;
};
