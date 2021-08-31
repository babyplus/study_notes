#include "iObject.h"

class Client : public IObject
{
    public:
        Client();
        virtual ~Client();
        virtual void subscribe(IObject*);
        virtual void publish(std::string&);
};
