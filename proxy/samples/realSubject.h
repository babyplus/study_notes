#ifndef __REALSUBJECT__
#define __REALSUBJECT__
#include "proxySubject.h"

class RealSubject : private ISubject
{
    public:
        RealSubject();
        virtual ~RealSubject();
        friend class ProxySubject;
    private:
        virtual void process();
};
#endif
