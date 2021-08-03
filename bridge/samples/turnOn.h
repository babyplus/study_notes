#include "operation.h"

class TurnOn : public Operation
{
    public:
        TurnOn();
        TurnOn(IObject*);
        virtual ~TurnOn();
        virtual void control(IObject*);
};
