#include "destination.h"

class Toilet : public Destination
{
    public:
        Toilet();
        virtual ~Toilet();
        virtual void accept(Vistor*);
        virtual void programme(const std::string&);
};
