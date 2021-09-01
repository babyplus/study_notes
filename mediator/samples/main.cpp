#include <pthread.h>
#include "messageQueue.h"
#include "client.h"

#define NUM_THREADS 5

static void* add_clients(void* args)
{
    TRACK();
    Client* client = new Client();
    client->subscribe((IObject*)args);
    return 0;
}

int main()
{
    MessageQueue mq = MessageQueue();

    pthread_t tids[NUM_THREADS];
    for(int i = 0; i < NUM_THREADS; ++i)
    {
        TRACK("%i", i);
        int ret = pthread_create(&tids[i], NULL, add_clients, &mq);
        if (ret != 0) TRACK("pthread_create error: error_code=%d", ret);
        pthread_join(tids[i], NULL);
    }

    TRACK("------------------------------------");

    Client client = Client();
    client.subscribe(&mq);
    std::string str = "0123456789";
    client.publish(str);
    return 0;
}
