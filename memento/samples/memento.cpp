#include "memento.h"

Memento::Memento()
{
    TRACK("begin");
}

Memento::Memento(const std::string state)
{
    TRACK("begin");
    this->state = state;
}

Memento::~Memento()
{
    TRACK("end");
}

std::string Memento::get_state() const
{
    return state;
}

void Memento::set_state(const std::string state)
{
    this->state = state;
}
