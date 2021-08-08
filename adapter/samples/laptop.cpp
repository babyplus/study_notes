#include "laptop.h"

Laptop::Laptop(Power* input)
{
    TRACK("begin");
    this->input = input;
}

Laptop::~Laptop()
{
    TRACK("end");
}

