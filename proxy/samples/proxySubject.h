#ifndef __PROXYSUBJECT__
#define __PROXYSUBJECT__
#include "isubject.h"
#include "realSubject.h"

class ProxySubject : public ISubject
{
    public:
        ProxySubject();
        virtual ~ProxySubject();
        virtual void process();
};
#endif
