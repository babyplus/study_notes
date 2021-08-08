#include "laptopPowerAdapter.h"
#include "delete.h"

LaptopPowerAdapter::LaptopPowerAdapter(Power220V* input):PowerAdapter(input)
{
    TRACK("begin");
    Power19V* output = new Power19V();
    this->output = output;
}


LaptopPowerAdapter::~LaptopPowerAdapter()
{
    TRACK("end");
    DELETE(this->output);
}
