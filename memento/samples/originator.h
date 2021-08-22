#include "memento.h"

class Originator
{
    std::string state;
    public:
        Originator();
        virtual ~Originator();
        Memento* create_memento();
        void set_memento(const Memento* memento);
        void update(const std::string state);
        void get_state();
};
