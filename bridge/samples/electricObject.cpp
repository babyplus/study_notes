#include "electricObject.h"

ElectricObject::ElectricObject()
{
    TRACK("begin");
}

ElectricObject::~ElectricObject()
{
    TRACK("end");
}

void ElectricObject::open()
{
    TRACK();
    supply_power();
}

void ElectricObject::close()
{
    TRACK();
    interrupt_power();
}

void ElectricObject::supply_power()
{
    TRACK();
}

void ElectricObject::interrupt_power()
{
    TRACK();
}

