#include "vistor.h"

class AMapVistor : public Vistor
{
    public:
        AMapVistor();
        virtual ~AMapVistor();
        virtual void find_restaurant(const std::string&);
        virtual void find_toilet(const std::string&);
};
