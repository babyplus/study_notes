#ifndef COMMAND
#define COMMAND
#include "tracker.h"
#include "receiver.h"

class Command
{
    protected:
        Receiver* receiver;
    public:
        Command(Receiver*);
        virtual ~Command();
        virtual void execute() = 0;
};
#endif
