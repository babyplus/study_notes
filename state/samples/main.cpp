#include "onState.h"
#include "offState.h"
#include "processor.h"

int main()
{
    TRACK();
    State* s = OffState::get_instance();
    Processor* p = new Processor(s);
    p->operation_1();
    p->operation_0();
    p->operation_1();
    p->operation_0();
    p->operation_1();
    p->operation_0();
    p->operation_1();
    return 0;
}
