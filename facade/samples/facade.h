#include <unordered_map>
#include <string>
#include "tracker.h"
#include "sub_system.h"

class Facade
{
    private:
        std::unordered_map<std::string, SubSystem*> sub_systems;
    public:
        Facade();
        virtual ~Facade();
        virtual void add_system(const std::string&, SubSystem*);
        virtual void methodA();
        virtual void methodB();
};
