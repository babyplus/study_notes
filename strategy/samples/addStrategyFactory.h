#include "strategyFactory.h"
#include "addStrategy.h"

class AddStrategyFactory : public StrategyFactory
{
    public:
        AddStrategyFactory();
        virtual ~AddStrategyFactory();
        virtual Strategy* create();
};
