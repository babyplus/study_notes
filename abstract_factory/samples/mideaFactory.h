#include "factory.h"
#include "iAircondition.h"
#include "iRemoteControl.h"
#include "tracker.h"

class MideaFactory : public Factory
{
    public:
        MideaFactory(); 
        virtual ~MideaFactory();
        virtual IAircondition* produce_aircondition();
        virtual IRemoteControl* produce_remote_control();
};
