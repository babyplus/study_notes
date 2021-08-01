#include "decoratorStream.h"

DecoratorStream::DecoratorStream(Stream* stm):stm(stm)
{
    TRACK("begin");
}

DecoratorStream::~DecoratorStream()
{
    TRACK("end");
}
