#include "power.h"

Power::Power(float voltage, float current, power_type_e type)
{
    TRACK("begin");
    this->voltage = voltage;
    this->current = current;
    this->type = type;
}

Power::~Power()
{
    TRACK("end");
}

