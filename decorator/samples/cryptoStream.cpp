#include "cryptoStream.h"

CryptoStream::CryptoStream(Stream* stm):DecoratorStream(stm)
{
    TRACK("begin");
}

CryptoStream::~CryptoStream()
{
    TRACK("end");
}

ssize_t CryptoStream::read(int fd, void *buf, size_t count)
{
    TRACK("do something special before read");
    stm->read(fd, buf, count);
    TRACK("do something special after read");
}

int CryptoStream::seek(int fd, long offset)
{
    TRACK();
}

ssize_t CryptoStream::write(int fd, void *buf, size_t count)
{
    TRACK();
}

