#include "authInterceptor.h"

AuthInterceptor::AuthInterceptor()
{
    TRACK("begin");
}

AuthInterceptor::~AuthInterceptor()
{
    TRACK("end");
}

bool AuthInterceptor::process(Action* action)
{
    TRACK();
    return true;
}
