#include "stream.h"

class DecoratorStream : public Stream
{
protected:
    Stream* stm;
    DecoratorStream(Stream* stm);
    virtual ~DecoratorStream();
};
