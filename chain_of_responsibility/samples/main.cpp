#include "action.h"
#include "interceptorChain.h"
#include "authInterceptor.h"
#include "auditInterceptor.h"

int main()
{
    InterceptorChain* chain = new InterceptorChain();
    Interceptor* authInterceptor = new AuthInterceptor();
    Interceptor* auditInterceptor = new AuditInterceptor();
    chain->add(authInterceptor);
    chain->add(auditInterceptor);

    Action* action = new Action();
    chain->process(action);

    DELETE(chain);
    DELETE(authInterceptor);
    DELETE(auditInterceptor);
    DELETE(action);
    return 0;
}
