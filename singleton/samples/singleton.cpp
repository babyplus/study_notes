#include "singleton.h"
#include "tracker.h"

Singleton::Singleton()
{
    TRACK("begin");
}

Singleton::~Singleton()
{
    TRACK("end");
}

#ifndef __MULTITHREAD__
Singleton* Singleton::m_instance=nullptr;
Singleton* Singleton::get_instance()
{
    if (m_instance == nullptr)
    {
        m_instance = new Singleton();
    }
    return m_instance;
}
#endif

#ifdef __MEYERS__
//Meyers' Singleton
Singleton* Singleton::get_instance()
{
    static Singleton instance;
    return &instance;    
}
#endif

#ifdef __ATOMIC_MUTEX__
//atomic & mutex
std::atomic<Singleton*> Singleton::m_instance;
std::mutex Singleton::m_mutex;
Singleton* Singleton::get_instance()
{
    Singleton* tmp = m_instance.load(std::memory_order_relaxed);
    std::atomic_thread_fence(std::memory_order_acquire);
    if (tmp == nullptr)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        tmp = m_instance.load(std::memory_order_relaxed);
        if (tmp == nullptr)
    {
        tmp = new Singleton;
        std::atomic_thread_fence(std::memory_order_release);
        m_instance.store(tmp, std::memory_order_relaxed);
    }
}
return tmp;
}
#endif
