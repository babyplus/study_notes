#include "invoker.h"

Invoker::Invoker()
{
    TRACK("begin");
}

Invoker::~Invoker()
{
    TRACK("end");
}

void Invoker::call(Command* command)
{
    TRACK();
    command->execute();
}
