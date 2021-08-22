#include "originator.h"

Originator::Originator()
{
    TRACK("begin");
}

Originator::~Originator()
{
    TRACK("end");
}

void Originator::update(const std::string state)
{
    this->state = state;
}

Memento* Originator::create_memento()
{
    Memento* memento = new Memento();
    memento->set_state(this->state);
    return memento;
}

void Originator::set_memento(const Memento* memento)
{
    this->state = memento->get_state();
}

void Originator::get_state()
{
    TRACK("%s", this->state.c_str());
}
