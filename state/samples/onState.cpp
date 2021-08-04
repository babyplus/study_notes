#include "offState.h"
#include "onState.h"

State* OnState::state = nullptr;

State* OnState::get_instance()
{
    if(nullptr == state)
    {
        state = new OnState();
    }
    TRACK("%p", state);
    return state;
}

OnState::OnState()
{
    TRACK("begin");
    if(nullptr == state)
    {
        state = this;
    }
}

OnState::~OnState()
{
    TRACK("end");
}

void OnState::operation_0()
{
    TRACK();
    p_next = OnState::get_instance();
}

void OnState::operation_1()
{
    TRACK();
    p_next = OffState::get_instance();
}
