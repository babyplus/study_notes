#include "isubject.h"

ISubject::ISubject()
{
    TRACK("begin");
}

ISubject::~ISubject()
{
    TRACK("end");
}

