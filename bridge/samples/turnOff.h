#include "operation.h"

class TurnOff : public Operation
{
    public:
        TurnOff();
        TurnOff(IObject*);
        virtual ~TurnOff();
        virtual void control(IObject*);
};
