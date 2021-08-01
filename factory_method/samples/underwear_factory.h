#include "factory.h"

class UnderwearFactory : public Factory
{
    public:
        UnderwearFactory();
        virtual ~UnderwearFactory();
        virtual int produce();
};
