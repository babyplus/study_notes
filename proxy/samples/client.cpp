#include "client.h"

Client::Client(ProxySubject* proxy)
{
    TRACK("begin");
    this->proxy = proxy;
}

Client::~Client()
{
    TRACK("end");
}

void Client::do_task()
{
    TRACK();
    if (nullptr != this->proxy)
    {
        this->proxy->process();
    }
}
