#ifndef SUB_SYSTEM
#define SUB_SYSTEM

#include "tracker.h"

class SubSystem
{
    public:
        SubSystem() {TRACK("begin")};
        virtual ~SubSystem() {TRACK("end")};
        virtual void method() = 0;
};

#endif
