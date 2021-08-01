#include "factory.h"

class ToyFactory : public Factory
{
    public:
        ToyFactory();
        virtual ~ToyFactory();
        virtual int produce();
};
