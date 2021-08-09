#include "component.h"
#include <string>

class Element : public Component
{
    private:
        std::string name;
    public:
        Element(const std::string&);
        virtual ~Element();
        virtual void process();
};
