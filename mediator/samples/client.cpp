#include "client.h"

Client::Client()
{
    TRACK("begin");
}

Client::~Client()
{
    TRACK("end");
}

void Client::subscribe(IObject* ob)
{
    TRACK();
    add_peer(ob);
    ob->add_peer(this);
}

void Client::publish(std::string& message)
{
    TRACK();
    for(auto peer:peers)
    {
        peer->recieve(message);
    }
}
