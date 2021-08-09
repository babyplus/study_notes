#include "singleton.h"
#include "tracker.h"
#ifdef __MULTITHREAD__
#include <pthread.h>
#endif

#define NUM_THREADS 10

#ifdef __MULTITHREAD__
void* test(void* args)
{
    Singleton* s = Singleton::get_instance();
    TRACK("%p", s);
}
#endif

int main()
{
#ifndef __MULTITHREAD__
    Singleton* s0 = Singleton::get_instance();
    TRACK("%p", s0);
    Singleton* s1 = Singleton::get_instance();
    TRACK("%p", s1);
    Singleton* s2 = Singleton::get_instance();
    TRACK("%p", s2);
    Singleton* s3 = Singleton::get_instance();
    TRACK("%p", s3);
#else
    pthread_t tids[NUM_THREADS];
    for(int i = 0; i < NUM_THREADS; ++i)
    {
        int ret = pthread_create(&tids[i], NULL, test, NULL);
        if (0 != ret)
        {
            TRACK("pthread_create error: error_code=%d", ret);
        }
    }
    pthread_exit(NULL);
#endif
    return 0;
}
