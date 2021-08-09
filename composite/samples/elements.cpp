#include "elements.h"

Elements::Elements(const std::string& name)
{
    TRACK("begin");
    this->name = name;
}

Elements::~Elements()
{
    TRACK("end");
}

void Elements::add(Component* e)
{
    this->elements.push_back(e);
}

void Elements::remove(Component* e)
{
    this->elements.remove(e);
}

void Elements::process()
{
    TRACK("elements: ----%s", this->name.c_str());
    for (std::list<Component*>::iterator it=this->elements.begin(); it != elements.end(); ++it)
    {
        (*it)->process();
    }
}

