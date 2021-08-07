#include "delete.h"
#include "turnOn.h"
#include "turnOff.h"
#include "electricObject.h"

int main()
{
    ElectricObject* ob = new ElectricObject();
    Operation* on = new TurnOn(ob);
    DELETE(on);
    TRACK("--------------------");
    Operation* off = new TurnOff();
    off->control(ob);
    DELETE(off);
    DELETE(ob);
}
