#include <list>
#include "interceptor.h"

class InterceptorChain
{
    private:
        std::list<Interceptor*> chain;
    public:
        InterceptorChain();
        virtual ~InterceptorChain();
        virtual void add(Interceptor*);
        virtual bool process(Action*);
};
