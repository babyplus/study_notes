#ifndef __COLLECTIONITERATOR__
#define __COLLECTIONITERATOR__
#include "myIterator.h"
#include "delete.h"
#include "tracker.h"

template<typename P>
class MyIterator
{
    private:
        const P* p_items;
        long current;
    public:

        MyIterator(const P* p_items)
        {
            TRACK("begin");
            this->p_items = p_items;
            current = 0;
        }
        
        virtual ~MyIterator()
        {
            TRACK("end");
        }
        
        
        virtual void  first()
        {
            TRACK();
            current = 0;
        }
        
        virtual void  next()
        {
            TRACK();
            ++current;
        }
        
        virtual bool is_done() const
        {
            return current < p_items->count();
        }

        virtual long get_current()
        {
            return current;
        }
};
#endif
