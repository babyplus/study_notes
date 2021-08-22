#include <string>
#include "tracker.h"

class Memento
{
    std::string state;
    public:
        Memento();
        Memento(const std::string state);
        virtual ~Memento();
        std::string get_state() const;
        void set_state(const std::string state);
};
