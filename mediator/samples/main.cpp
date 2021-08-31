#include <pthread.h>
#include "messageQueue.h"
#include "client.h"

#define NUM_THREADS 5

static void* say_hello(void* args)
{
    TRACK();
    return 0;
}

int main()
{
    pthread_t tids[NUM_THREADS];
    for(int i = 0; i < NUM_THREADS; ++i)
    {
        TRACK("%i", i);
        int ret = pthread_create(&tids[i], NULL, say_hello, NULL);
        if (ret != 0) TRACK("pthread_create error: error_code=%d", ret);
    }
    return 0;
}
