#include "facade.h"
#include "sub_systems.h"

int main()
{
    SubSystemA a = SubSystemA();
    SubSystemB b = SubSystemB();
    SubSystemC c = SubSystemC();
    SubSystemD d = SubSystemD();

    Facade facade = Facade();
    facade.add_system("a", &a);
    facade.add_system("b", &b);
    facade.add_system("c", &c);
    facade.add_system("d", &d);

    facade.methodA();
    facade.methodB();
    return 0;
}
