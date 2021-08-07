#include "addStrategyFactory.h"

AddStrategyFactory::AddStrategyFactory()
{
    TRACK("begin");
}

AddStrategyFactory::~AddStrategyFactory()
{
    TRACK("end");
}

Strategy* AddStrategyFactory::create()
{
    Strategy* strategy = new AddStrategy();
    return strategy;
}
