#include "stream.h"

class FileStream : public Stream
{
    public:
        FileStream();
        virtual ~FileStream();
        virtual ssize_t read(int fd, void *buf, size_t count);
        virtual int seek(int fd, long offset);
        virtual ssize_t write(int fd, void *buf, size_t count);
};
