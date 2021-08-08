#include "tracker.h"

class Prototype
{
    public:
        Prototype();
        virtual ~Prototype();
        virtual Prototype* clone();
};
