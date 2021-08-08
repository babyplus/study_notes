#include "power.h"

class Laptop
{
    private:
        Power* input;
    public:
        Laptop(Power*);
        virtual  ~Laptop();
};
