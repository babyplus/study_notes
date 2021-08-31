#include "iObject.h"

class MessageQueue : public IObject
{
    public:
        MessageQueue();
        virtual ~MessageQueue();
        virtual void recieve(std::string&);
};
