#include "originator.h"
#include "delete.h"

int main()
{
    Originator originator;
    originator.get_state();
    originator.update("0");
    originator.get_state();
    Memento* memento = originator.create_memento();
    originator.update("1");
    originator.get_state();
    originator.set_memento(memento);
    originator.get_state();

    DELETE(memento);

    return 0;
}
