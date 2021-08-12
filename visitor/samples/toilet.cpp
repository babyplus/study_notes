#include "toilet.h"

Toilet::Toilet()
{
    TRACK("begin");
}

Toilet::~Toilet()
{
    TRACK("end");
}

void Toilet::accept(Vistor* vistor)
{
    TRACK();
    this->vistor = vistor;
}

void Toilet::programme(const std::string& name)
{
    TRACK();
    vistor->find_toilet(name);
}
