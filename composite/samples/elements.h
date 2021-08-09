#include "component.h"
#include <list>
#include <string>

class Elements : public Component
{
    private:
        std::string name;
        std::list<Component*> elements;
    public:
        Elements(const std::string&);
        virtual ~Elements();
        virtual void add(Component*);
        virtual void remove(Component*);
        virtual void process();
};
