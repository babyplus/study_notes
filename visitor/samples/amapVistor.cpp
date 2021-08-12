#include "amapVistor.h"

AMapVistor::AMapVistor()
{
    TRACK("begin");
}

AMapVistor::~AMapVistor()
{
    TRACK("end");
}

void AMapVistor::find_restaurant(const std::string& name)
{
    TRACK();
}

void AMapVistor::find_toilet(const std::string& name)
{
    TRACK();
}

