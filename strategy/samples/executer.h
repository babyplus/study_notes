#include "delete.h"
#include "strategyFactory.h"

class Executer
{
private:
    StrategyFactory* strategyFactory;
public:
    Executer(StrategyFactory*);
    virtual ~Executer();
    virtual void execute();
    virtual void rebind(StrategyFactory*);
};
