#include "salesman.h"

Salesman::Salesman(Factory* factory):factory(factory)
{
    TRACK("begin");
}

Salesman::~Salesman()
{
    TRACK("end");
    DELETE(factory);
}

void Salesman::order()
{
    TRACK();
    factory->produce();
}

