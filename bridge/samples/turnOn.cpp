#include "turnOn.h"

TurnOn::TurnOn()
{
    TRACK("begin");
}

TurnOn::TurnOn(IObject* ob)
{
    TRACK("begin");
    control(ob);
}

TurnOn::~TurnOn()
{
    TRACK("end");
}

void TurnOn::control(IObject* ob)
{
    ob->open();
}
