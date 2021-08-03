#include "operation.h"

Operation::Operation()
{
    TRACK("begin");
}

Operation::~Operation()
{
    TRACK("end");
}

