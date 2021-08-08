#include "powerAdapter.h"
#include "power220V.h"
#include "power19V.h"

class LaptopPowerAdapter : public PowerAdapter<Power220V, Power19V>
{
    public:
        LaptopPowerAdapter(Power220V*);
        virtual ~LaptopPowerAdapter();
};
