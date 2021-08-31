#include "concreate_command.h"

ConcreateCommand::ConcreateCommand(Receiver* receiver) : Command(receiver)
{
    TRACK("begin");
}

ConcreateCommand::~ConcreateCommand()
{
    TRACK("end");
}


void ConcreateCommand::execute()
{
    TRACK();
    this->receiver->action();
}
