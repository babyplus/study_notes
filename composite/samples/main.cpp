#include "elements.h"
#include "element.h"

int main()
{
    Elements els0("0");
    Elements els01("01");
    Elements els11("11");
    Elements els23("23");
    Element el00("00");
    Element el10("10");
    Element el20("20");
    Element el21("21");
    Element el22("22");

    els0.add(&el00);
    els0.add(&els01);

    els01.add(&el10);
    els01.add(&els11);

    els11.add(&el20);
    els11.add(&el21);
    els11.add(&el22);
    els11.add(&els23);

    els0.process();

    return 0;
}
