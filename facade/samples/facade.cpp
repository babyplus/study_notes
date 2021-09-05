#include "facade.h"

Facade::Facade()
{
    TRACK("begin");
}

Facade::~Facade()
{
    TRACK("end");
}

void Facade::add_system(const std::string& key, SubSystem* value)
{
    TRACK();
    sub_systems.emplace(key, value);
}

void Facade::methodA()
{
    TRACK();
    sub_systems["a"]->method();
    sub_systems["b"]->method();
}

void Facade::methodB()
{
    TRACK();
    sub_systems["c"]->method();
    sub_systems["d"]->method();
}
