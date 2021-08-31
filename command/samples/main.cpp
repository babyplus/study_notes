#include "invoker.h"
#include "concreate_command.h"

int main()
{
    Receiver receiver = Receiver();
    ConcreateCommand command = ConcreateCommand(&receiver);
    Invoker invoker = Invoker();
    invoker.call(&command);
    return 0;
}
