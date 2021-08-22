#include "amapVistor.h"
#include "baiduVistor.h"
#include "restaurant.h"
#include "toilet.h"

int main()
{
    AMapVistor av = AMapVistor();
    BaiduVistor bv = BaiduVistor();
    Restaurant restaurant = Restaurant();
    Toilet toilet = Toilet();

    restaurant.accept(&av);
    restaurant.programme("McDonald's");

    toilet.accept(&bv);
    toilet.programme("KFC");

    return 0;
}
