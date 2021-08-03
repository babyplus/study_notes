#include "turnOn.h"
#include "turnOff.h"
#include "electricObject.h"

int main()
{
    ElectricObject* ob = new ElectricObject();
    Operation* on = new TurnOn(ob);
    delete on;
    TRACK("--------------------");
    Operation* off = new TurnOff();
    off->control(ob);
    delete off;
    delete ob;
}
