#include "state.h"

class OffState : public State
{
    public:
        static State* state;
        static State* get_instance();
        void operation_0();
        void operation_1();

    private:
        OffState();
        virtual ~OffState();
};

