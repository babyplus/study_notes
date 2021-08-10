#include "proxySubject.h"

class Client
{
    public:
        Client(ProxySubject*);
        virtual ~Client();
        void do_task();
    private:
        ProxySubject* proxy;
};
