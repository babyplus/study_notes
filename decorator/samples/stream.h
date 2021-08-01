#ifndef __STREAM__
#define __STREAM__
#include "tracker.h"

class Stream
{
public:
    virtual ~Stream(){};
    virtual ssize_t read(int fd, void *buf, size_t count) = 0;
    virtual int seek(int fd, long offset) = 0;
    virtual ssize_t write(int fd, void *buf, size_t count) = 0;
};
#endif
