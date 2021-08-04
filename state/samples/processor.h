#include "state.h"

class Processor
{
    private:
        State* state;
        
    public:
        Processor(State*);
        virtual ~Processor();
        virtual void operation_0();
        virtual void operation_1();
};
