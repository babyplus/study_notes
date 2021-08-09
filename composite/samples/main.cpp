#include "elements.h"
#include "element.h"
#include "delete.h"

int main()
{
    Elements* els0 = new Elements("0");
    Elements* els01 = new Elements("01");
    Elements* els11 = new Elements("11");
    Elements* els23 = new Elements("23");
    Element* el00 = new Element("00");
    Element* el10 = new Element("10");
    Element* el20 = new Element("20");
    Element* el21 = new Element("21");
    Element* el22 = new Element("22");

    els0->add(el00);
    els0->add(els01);

    els01->add(el10);
    els01->add(els11);

    els11->add(el20);
    els11->add(el21);
    els11->add(el22);
    els11->add(els23);

    els0->process();

    DELETE(els0); 
    DELETE(els01);
    DELETE(els11);
    DELETE(els23);
    DELETE(el00); 
    DELETE(el10); 
    DELETE(el20); 
    DELETE(el21); 
    DELETE(el22); 
    return 0;
}
