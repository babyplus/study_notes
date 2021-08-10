#include "interceptorChain.h"

InterceptorChain::InterceptorChain()
{
    TRACK("begin");
}

InterceptorChain::~InterceptorChain()
{
    TRACK("end");
}

void InterceptorChain::add(Interceptor* interceptor)
{
    chain.push_back(interceptor);
}

bool InterceptorChain::process(Action* action)
{
    for(auto i : chain)
    {
        i->process(action);
    }
    action->execute();
    return true;
}
