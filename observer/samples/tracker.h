#ifndef TRACK
#include <cstdio>
#define TRACK(code, ...) printf("%s(%d) --> \"%s\" " code "\n" , __FILE__, __LINE__, __PRETTY_FUNCTION__,  ##__VA_ARGS__);
#endif
