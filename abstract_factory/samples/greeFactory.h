#include "factory.h"
#include "iAircondition.h"
#include "iRemoteControl.h"
#include "tracker.h"

class GreeFactory : public Factory
{
    public:
        GreeFactory(); 
        virtual ~GreeFactory();
        virtual IAircondition* produce_aircondition();
        virtual IRemoteControl* produce_remote_control();
};
