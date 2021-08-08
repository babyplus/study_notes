#include "power220V.h"

Power220V::Power220V():Power(220,1.5,ALTERNATING)
{
    TRACK("begin");
}

Power220V::~Power220V()
{
    TRACK("end");
}
