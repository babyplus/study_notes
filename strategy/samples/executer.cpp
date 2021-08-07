#include "executer.h"

Executer::Executer(StrategyFactory* strategyFactory)
{
    TRACK("begin");
    this->strategyFactory = strategyFactory;
}

Executer::~Executer()
{
    TRACK("end");
    DELETE(this->strategyFactory);
}

void Executer::execute()
{
    Strategy* strategy = this->strategyFactory->create();
    strategy->execute();
    DELETE(strategy);
}

void Executer::rebind(StrategyFactory* strategyFactory)
{
    DELETE(this->strategyFactory);
    this->strategyFactory = strategyFactory;
}

