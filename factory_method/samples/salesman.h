#include "factory.h"

class Salesman
{
    private:
        Factory* factory;
    public:
        Salesman(Factory*);
        ~Salesman();
        virtual void order();
};
