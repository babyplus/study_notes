#include "receiver.h"

Receiver::Receiver()
{
    TRACK("begin");
}

Receiver::~Receiver()
{
    TRACK("end");
}

void Receiver::action()
{
    TRACK();
}
