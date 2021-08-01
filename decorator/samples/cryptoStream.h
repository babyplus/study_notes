#include "decoratorStream.h"

class CryptoStream : public DecoratorStream 
{
    public:
        CryptoStream(Stream* stm);
        virtual ~CryptoStream();
        virtual ssize_t read(int fd, void *buf, size_t count);
        virtual int seek(int fd, long offset);
        virtual ssize_t write(int fd, void *buf, size_t count);
};
