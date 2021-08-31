#include "command.h"

class ConcreateCommand : public Command
{
    public:
        ConcreateCommand(Receiver*);
        virtual ~ConcreateCommand();
        virtual void execute();
};
