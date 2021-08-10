#include "interceptor.h"
#include "action.h"

class AuthInterceptor : public Interceptor
{
    public:
        AuthInterceptor(); 
        virtual ~AuthInterceptor(); 
        virtual bool process(Action*); 
};
