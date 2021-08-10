#include "interceptor.h"
#include "action.h"

class AuditInterceptor : public Interceptor
{
    public:
        AuditInterceptor(); 
        virtual ~AuditInterceptor(); 
        virtual bool process(Action*); 
};
