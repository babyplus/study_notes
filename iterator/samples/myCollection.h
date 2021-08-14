#ifndef __COLLECTION__
#define __COLLECTION__
#include <vector>
#include "myIterator.h"

template<typename Item>
class MyCollection
{
    private:
        std::vector<Item> items;
        MyIterator<MyCollection<Item>>* p_iterator;

    public:
        MyCollection()
        {
            TRACK("begin");
            p_iterator = nullptr;
        }
        
        ~MyCollection()
        {
            TRACK("end");
            if(nullptr != this->p_iterator)
            {
                DELETE(this->p_iterator);
            }
        }
        
        MyIterator<MyCollection<Item>>* get_iterator()
        {
            if(nullptr == this->p_iterator)
            {
                this->p_iterator = new MyIterator<MyCollection<Item>>(this);
            }
            return this->p_iterator;
        }
        
        long count() const
        {
            return items.size();
        }
        
        void add(Item item)
        {
            items.push_back(item);
        }
        
        Item get(long index)
        {
            return items[index];
        }
};
#endif
