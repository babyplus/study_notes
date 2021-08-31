#include "iObject.h"

IObject::IObject()
{
    TRACK("begin");
}

IObject::~IObject()
{
    TRACK("end");
}

void IObject::recieve(std::string& message)
{
    TRACK("%s", message.c_str());
}

void IObject::add_peer(IObject* ob)
{
    TRACK();
    peers.push_back(ob);
}
