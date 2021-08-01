#include "toy_factory.h"

ToyFactory::ToyFactory()
{
    TRACK("begin");
}

ToyFactory::~ToyFactory()
{
    TRACK("end");
}

int ToyFactory::produce()
{
    TRACK();
}
