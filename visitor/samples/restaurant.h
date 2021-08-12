#include "destination.h"

class Restaurant : public Destination
{
    public:
        Restaurant();
        virtual ~Restaurant();
        virtual void accept(Vistor*);
        virtual void programme(const std::string&);
};
