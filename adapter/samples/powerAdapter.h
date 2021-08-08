#ifndef __POWERADPTER__
#define __POWERADPTER__
#include "power.h"

template<class I, class O>
class PowerAdapter
{
    protected:
        I* input;
        O* output;
    public:
        PowerAdapter(I*);
        virtual ~PowerAdapter();
        virtual O* get_output();
};

template<class I, class O>
PowerAdapter<I,O>::PowerAdapter(I* input)
{
    TRACK("begin");
    this->input = input;
    this->output = nullptr;
}

template<class I, class O>
PowerAdapter<I,O>::~PowerAdapter()
{
    TRACK("end");
}

template<class I, class O>
O* PowerAdapter<I,O>::get_output()
{
    return this->output;
}
#endif
