#include "salesman.h"
#include "toy_factory.h"
#include "underwear_factory.h"

int main()
{
    ToyFactory tft = ToyFactory();
    Salesman m1 = Salesman(&tft);
    m1.order();
    TRACK("---------------------------");
    UnderwearFactory uwft = UnderwearFactory();
    Salesman m2 = Salesman(&uwft);
    m2.order();
    return 0;
}
