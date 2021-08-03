#include "salesman.h"
#include "toy_factory.h"
#include "underwear_factory.h"

int main()
{
    Factory* tft1 = new ToyFactory();
    Salesman* m1 = new Salesman(tft1);
    m1->order();
    delete m1;
    TRACK("---------------------------");
    Factory* tft2 = new UnderwearFactory();
    Salesman* m2 = new Salesman(tft2);
    m2->order();
    delete m2;
    return 0;
}
