#include "element.h"

Element::Element(const std::string& name)
{
    TRACK("begin");
    this->name = name;
}

Element::~Element()
{
    TRACK("end");
}

void Element::process()
{
    TRACK("element: --%s", this->name.c_str());
}

