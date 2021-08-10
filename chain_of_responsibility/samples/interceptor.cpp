#include "interceptor.h"

Interceptor::Interceptor()
{
    TRACK("begin");
}

Interceptor::~Interceptor()
{
    TRACK("end");
}

