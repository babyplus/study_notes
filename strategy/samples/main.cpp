#include "executer.h"
#include "addStrategyFactory.h"
#include "removeStrategyFactory.h"

int main()
{
    StrategyFactory* add_sf = new AddStrategyFactory();
    Executer* executer = new Executer(add_sf);
    executer->execute();
    TRACK("---------------------------");
    StrategyFactory* rm_sf = new RemoveStrategyFactory();
    executer->rebind(rm_sf);
    executer->execute();
    DELETE(executer);
    return 0;
}

