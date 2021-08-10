#include "realSubject.h"

RealSubject::RealSubject()
{
    TRACK("begin");
}

RealSubject::~RealSubject()
{
    TRACK("end");
}

void RealSubject::process()
{
    TRACK("real...");
}
