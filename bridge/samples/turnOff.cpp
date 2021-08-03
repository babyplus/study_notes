#include "turnOff.h"

TurnOff::TurnOff()
{
    TRACK("begin");
}

TurnOff::TurnOff(IObject*)
{
    TRACK("begin");
    control(ob);
}

TurnOff::~TurnOff()
{
    TRACK("end");
}

void TurnOff::control(IObject* ob)
{
    ob->close();
}
