#ifndef IOBJECT
#define IOBJECT

#include <string>
#include <vector>
#include "tracker.h"

class IObject
{
    protected:
        std::vector<IObject*> peers;
    public:
        IObject();
        virtual ~IObject();
        virtual void recieve(std::string&);
        virtual void add_peer(IObject*);
};

#endif
