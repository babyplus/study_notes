#include "prototype.h"
#include "delete.h"

int main()
{
    Prototype* p0 = new Prototype();
    Prototype* p1 = p0->clone();
    Prototype* p2 = p0->clone();
    DELETE(p2);
    DELETE(p1);
    DELETE(p0);
    return 0;
}
