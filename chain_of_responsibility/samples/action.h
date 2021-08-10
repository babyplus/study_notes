#ifndef __ACTION__
#define __ACTION__
#include "tracker.h"
#include "delete.h"

class Action
{
    public:
        virtual bool execute();
};
#endif
