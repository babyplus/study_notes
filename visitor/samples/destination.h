#ifndef __DESTINATION__
#define __DESTINATION__
#include "tracker.h"
#include "vistor.h"
class Destination
{
    protected:
        Vistor* vistor;
    public:
        virtual void accept(Vistor*) = 0;
};
#endif
