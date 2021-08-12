#ifndef __VISTOR__
#define __VISTOR__
#include <string> 
#include "tracker.h"

class Vistor
{
    public:
        Vistor();
        virtual ~Vistor();
        virtual void find_restaurant(const std::string&) = 0;
        virtual void find_toilet(const std::string&) = 0;
};
#endif
