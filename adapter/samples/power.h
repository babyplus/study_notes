#ifndef __POWER__
#define __POWER__
#include "tracker.h"

class Power
{
    public:
       typedef enum power_type
       {
           DIRECT,
           ALTERNATING
       } power_type_e;
    private:
      float voltage;
      float current;
      power_type_e type;
    public:
      Power(float voltage, float current, power_type_e type);
      virtual ~Power();
};
#endif
