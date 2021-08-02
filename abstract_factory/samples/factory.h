#ifndef __FACTORY__
#define __FACTORY__
#include "tracker.h"
#include "iAircondition.h"
#include "iRemoteControl.h"

class Factory
{
    public:
        Factory();
        virtual ~Factory();
        virtual IAircondition* produce_aircondition() = 0;
        virtual IRemoteControl* produce_remote_control() = 0;
};
#endif
