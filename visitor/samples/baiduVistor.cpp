#include "baiduVistor.h"

BaiduVistor::BaiduVistor()
{
    TRACK("begin");
}

BaiduVistor::~BaiduVistor()
{
    TRACK("end");
}

void BaiduVistor::find_restaurant(const std::string& name)
{
    TRACK();
}

void BaiduVistor::find_toilet(const std::string& name)
{
    TRACK();
}

