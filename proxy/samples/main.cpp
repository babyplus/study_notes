#include "client.h"
#include "proxySubject.h"

int main()
{
    ProxySubject proxy = ProxySubject();
    Client client = Client(&proxy);
    client.do_task();
    return 0;
}
