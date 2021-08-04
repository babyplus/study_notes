#include "state.h"

class OnState : public State
{
    public:
        static State* state;
        static State* get_instance();
        void operation_0();
        void operation_1();

    private:
        OnState();
        virtual ~OnState();
};
