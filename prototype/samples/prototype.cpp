#include "prototype.h"

Prototype::Prototype()
{
    TRACK("begin");
}

Prototype::~Prototype()
{
    TRACK("end");
}

Prototype* Prototype::clone()
{
    TRACK("clone");
    return new Prototype(*this);
}

