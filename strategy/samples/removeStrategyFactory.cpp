#include "removeStrategyFactory.h"

RemoveStrategyFactory::RemoveStrategyFactory()
{
    TRACK("begin");
}

RemoveStrategyFactory::~RemoveStrategyFactory()
{
    TRACK("end");
}

Strategy* RemoveStrategyFactory::create()
{
    Strategy* strategy = new RemoveStrategy();
    return strategy;
}
