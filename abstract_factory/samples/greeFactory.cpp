#include "greeFactory.h"
#include "greeAircondition.h"
#include "greeRemoteControl.h"

GreeFactory::GreeFactory()
{
    TRACK("begin");
}

GreeFactory::~GreeFactory()
{
    TRACK("end");
}

IAircondition* GreeFactory::produce_aircondition()
{
    TRACK();
    IAircondition* i = new GreeAircondition();
    return i;
}

IRemoteControl* GreeFactory::produce_remote_control()
{
    TRACK();
    IRemoteControl* i = new GreeRemoteControl();
    return i;
}

