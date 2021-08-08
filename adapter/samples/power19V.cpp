#include "power19V.h"

Power19V::Power19V():Power(19,4.74,DIRECT)
{
    TRACK("begin");
}

Power19V::~Power19V()
{
    TRACK("end");
}
