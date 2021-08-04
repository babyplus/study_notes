#include "offState.h"
#include "onState.h"

State* OffState::state = nullptr;

State* OffState::get_instance()
{
    if(nullptr == state)
    {
        state = new OffState();
    }
    TRACK("%p", state);
    return state;
}

OffState::OffState()
{
    TRACK("begin");
    if(nullptr == state)
    {
        state = this;
    }
}

OffState::~OffState()
{
    TRACK("end");
}

void OffState::operation_0()
{
    TRACK();
    p_next = OffState::get_instance();
}

void OffState::operation_1()
{
    TRACK();
    p_next = OnState::get_instance();
}
