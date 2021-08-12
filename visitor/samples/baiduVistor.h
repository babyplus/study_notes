#include "vistor.h"

class BaiduVistor : public Vistor
{
    public:
        BaiduVistor();
        virtual ~BaiduVistor();
        virtual void find_restaurant(const std::string&);
        virtual void find_toilet(const std::string&);
};
