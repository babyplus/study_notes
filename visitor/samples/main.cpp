#include "amapVistor.h"
#include "baiduVistor.h"
#include "restaurant.h"
#include "toilet.h"
#include "delete.h"

int main()
{
    AMapVistor* av = new AMapVistor();
    BaiduVistor* bv = new BaiduVistor();
    Restaurant* restaurant = new Restaurant();
    Toilet* toilet = new Toilet();

    restaurant->accept(av);
    restaurant->programme("McDonald's");

    toilet->accept(bv);
    toilet->programme("KFC");

    DELETE(av);
    DELETE(bv);
    DELETE(restaurant);
    DELETE(toilet);

    return 0;
}
