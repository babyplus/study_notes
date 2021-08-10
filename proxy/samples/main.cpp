#include "client.h"
#include "proxySubject.h"

int main()
{
    ProxySubject* proxy = new ProxySubject();
    Client* client = new Client(proxy);
    client->do_task();
    DELETE(client);
    DELETE(proxy);
    return 0;
}
