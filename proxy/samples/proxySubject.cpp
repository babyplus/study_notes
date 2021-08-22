#include "proxySubject.h"

ProxySubject::ProxySubject()
{
    TRACK("begin");
}

ProxySubject::~ProxySubject()
{
    TRACK("end");
}

void ProxySubject::process()
{
    TRACK("proxy...");
    RealSubject r = RealSubject();
    r.process();
}
