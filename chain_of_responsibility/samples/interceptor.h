#ifndef __INTERCEPTOR__
#define __INTERCEPTOR__
#include "action.h"

class Interceptor
{
    public:
        Interceptor();
        virtual ~Interceptor();
        virtual bool process(Action*) = 0;
};
#endif
