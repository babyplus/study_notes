#include "strategy.h"

class RemoveStrategy : public Strategy
{
    public:
        RemoveStrategy();
        virtual ~RemoveStrategy();
        virtual void execute();
};
