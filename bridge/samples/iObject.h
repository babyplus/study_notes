#ifndef __IOBJECT__
#define __IOBJECT__
#include "tracker.h"

class IObject
{
    public:
        IObject();
        virtual ~IObject();
        virtual void open() = 0;
        virtual void close() = 0;
};
#endif
