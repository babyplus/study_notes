#ifndef TRACK
#include <cstdio>
#define TRACK(code, ...) printf("%50s(%3d) --> \"%s\" " code "\n" , __FILE__, __LINE__, __PRETTY_FUNCTION__,  ##__VA_ARGS__);
#endif
