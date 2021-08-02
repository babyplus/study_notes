#include "iRemoteControl.h"

IRemoteControl::IRemoteControl()
{
    TRACK("begin");
}

IRemoteControl::~IRemoteControl()
{
    TRACK("end");
}

bool IRemoteControl::bind(IAircondition*)
{
    TRACK("set value");
    return true;
}
