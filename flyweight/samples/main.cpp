#include "flyweight.h"
#include "delete.h"

int main()
{
    Flyweight* flyweight = new Flyweight();
    Entry* entry0 = flyweight->findEntryOrCreate("0");
    TRACK("%p", entry0);
    Entry* entry1 = flyweight->findEntryOrCreate("1");
    TRACK("%p", entry1);
    Entry* entry2 = flyweight->findEntryOrCreate("2");
    TRACK("%p", entry2);
    Entry* entry3 = flyweight->findEntryOrCreate("1");
    TRACK("%p", entry3);
    Entry* entry4 = flyweight->findEntryOrCreate("0");
    TRACK("%p", entry4);
    DELETE(flyweight);
    return 0;
}
