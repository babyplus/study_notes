#ifndef __FACTORY__
#define __FACTORY__
#include "tracker.h"

class Factory
{
    public:
        Factory();
        virtual ~Factory();
        virtual int produce() = 0;
};
#endif
