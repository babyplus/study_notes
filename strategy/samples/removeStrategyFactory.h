#include "strategyFactory.h"
#include "removeStrategy.h"

class RemoveStrategyFactory : public StrategyFactory
{
    public:
        RemoveStrategyFactory();
        virtual ~RemoveStrategyFactory();
        virtual Strategy* create();
};
