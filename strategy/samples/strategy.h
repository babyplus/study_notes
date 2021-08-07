#ifndef __STRATEGY__
#define __STRATEGY__
#include "tracker.h"

class Strategy
{
    public:
        Strategy();
        virtual ~Strategy();
        virtual void execute() = 0;
};
#endif
