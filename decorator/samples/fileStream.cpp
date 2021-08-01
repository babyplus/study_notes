#include "fileStream.h"

FileStream::FileStream()
{
    TRACK("begin");
}

FileStream::~FileStream()
{
    TRACK("end");
}

ssize_t FileStream::read(int fd, void *buf, size_t count)
{
    TRACK();
    return 0;
}
int FileStream::seek(int fd, long offset)
{
    TRACK();
    return 0;
}
ssize_t FileStream::write(int fd, void *buf, size_t count)
{
    TRACK();
    return 0;
}
