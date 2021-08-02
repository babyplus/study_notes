#ifndef __IREMOTECONTROL__
#define __IREMOTECONTROL__
#include "tracker.h"
#include "iAircondition.h"

class IRemoteControl
{
    public:
        IRemoteControl();
        virtual ~IRemoteControl();
        virtual bool bind(IAircondition*);
};
#endif
