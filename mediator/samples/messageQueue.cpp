#include "messageQueue.h"

MessageQueue::MessageQueue()
{
    TRACK("begin");
}

MessageQueue::~MessageQueue()
{
    TRACK("end");
}

void MessageQueue::recieve(std::string& message)
{
    TRACK();
    for(auto client:peers)
    {
        client->recieve(message);
    }
}
