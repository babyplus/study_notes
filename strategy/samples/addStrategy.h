#include "strategy.h"

class AddStrategy : public Strategy
{
    public:
        AddStrategy();
        virtual ~AddStrategy();
        virtual void execute();
};
