#include "processor.h"

Processor::Processor(State* state)
{
    TRACK("begin");
    this->state = state;
}

Processor::~Processor()
{
    TRACK("end");
}

void Processor::operation_0()
{
    TRACK();
    state->operation_0();
    this->state = state->p_next;
}

void Processor::operation_1()
{
    TRACK();
    state->operation_1();
    this->state = state->p_next;
}
