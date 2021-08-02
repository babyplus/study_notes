#include "mideaFactory.h"
#include "mideaAircondition.h"
#include "mideaRemoteControl.h"

MideaFactory::MideaFactory()
{
    TRACK("begin");
}

MideaFactory::~MideaFactory()
{
    TRACK("end");
}

IAircondition* MideaFactory::produce_aircondition()
{
    TRACK();
    IAircondition* i = new MideaAircondition();
    return i;
}

IRemoteControl* MideaFactory::produce_remote_control()
{
    TRACK();
    IRemoteControl* i = new MideaRemoteControl();
    return i;
}

