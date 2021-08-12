#include "restaurant.h"

Restaurant::Restaurant()
{
    TRACK("begin");
}

Restaurant::~Restaurant()
{
    TRACK("end");
}

void Restaurant::accept(Vistor* vistor)
{
    TRACK();
    this->vistor = vistor;
}

void Restaurant::programme(const std::string& name)
{
    TRACK();
    vistor->find_restaurant(name);
}
