#include "command.h"

Command::Command(Receiver* receiver)
{
    TRACK("begin");
    this->receiver = receiver;
}

Command::~Command()
{
    TRACK("end");
}
