#ifdef __ATOMIC_MUTEX__
#include <atomic>
#include <mutex>
#endif

class Singleton{
	private:
	    Singleton();
	    virtual ~Singleton();
	public:
	    Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;

#ifndef __MULTITHREAD__ 
	    static Singleton* get_instance();
	    static Singleton* m_instance;
#endif

#ifdef __MEYERS__
	    static Singleton* get_instance();
#endif

#ifdef __ATOMIC_MUTEX__
        static std::atomic<Singleton*> m_instance;
        static std::mutex m_mutex;
	    static Singleton* get_instance();
#endif
};

