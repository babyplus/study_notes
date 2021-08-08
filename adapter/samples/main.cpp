#include "power220V.h"
#include "power19V.h"
#include "laptop.h"
#include "laptopPowerAdapter.h"
#include "delete.h"

int main()
{
    Power220V* power_220V = new Power220V();
    LaptopPowerAdapter* adapter = new LaptopPowerAdapter(power_220V);
    Power19V* power_19V = adapter->get_output();
    Laptop* laptop = new Laptop(power_19V);
    DELETE(laptop);
    DELETE(adapter);
    DELETE(power_220V);
    return 0;
}
