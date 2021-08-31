#include "command.h"

class Invoker
{
    public:
        Invoker();
        virtual ~Invoker();
        virtual void call(Command*);
};
