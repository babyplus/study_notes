#include "flyweight.h"

Flyweight::Flyweight()
{
    TRACK("begin");
}

Flyweight::~Flyweight()
{
    TRACK("end");
    for(auto& it:pool)
    {
        DELETE(it.second);
    }
}

Entry* Flyweight::findEntryOrCreate(const std::string& key)
{
    TRACK();
    Entry* entry = nullptr;
    auto it = pool.find(key);
    if (pool.end() == it)
    {
        entry = new Entry();
        pool.emplace(key, entry);
    }else{
        entry = pool[key];
    }
    return entry;
}
