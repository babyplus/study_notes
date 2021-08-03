#include "tracker.h"
#include "iObject.h"

class ElectricObject : public IObject
{
    public:
        ElectricObject();
        virtual ~ElectricObject();
        virtual void open();
        virtual void close();

    private:
        virtual void supply_power();
        virtual void interrupt_power();
};
