#ifndef __STRATEGY_FACTORY__
#define __STRATEGY_FACTORY__
#include "tracker.h"
#include "strategy.h"

class StrategyFactory
{
    public:
        StrategyFactory();
        virtual ~StrategyFactory();
        virtual Strategy* create() = 0;
};
#endif
