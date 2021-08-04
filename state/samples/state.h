#ifndef __STATE__
#define __STATE__
#include "tracker.h"

class State
{
    public:
        State* p_next;
        State();
        virtual ~State();
        virtual void operation_0() = 0;
        virtual void operation_1() = 0;
};
#endif
