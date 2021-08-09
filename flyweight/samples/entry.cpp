#include "entry.h"

Entry::Entry()
{
    TRACK("begin");
}

Entry::~Entry()
{
    TRACK("end");
}

