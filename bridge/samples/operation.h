#ifndef __OPERATION__
#define __OPERATION__
#include "tracker.h"
#include "iObject.h"

class Operation
{
    protected:
        IObject* ob;

    public:
        Operation();
        virtual ~Operation();
        virtual void control(IObject*) = 0;
};
#endif
