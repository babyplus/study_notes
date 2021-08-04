#include "state.h"

State::State()
{
    TRACK("begin");
    p_next = nullptr;
}

State::~State()
{
    TRACK("end");
}

