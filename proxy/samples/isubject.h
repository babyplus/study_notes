#ifndef __ISUBJECT__
#define __ISUBJECT__
#include "tracker.h"

class ISubject
{
    public:
        ISubject();
        virtual ~ISubject();
        virtual void process() = 0;
};

#endif
