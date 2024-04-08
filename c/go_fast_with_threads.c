#include <pthread.h>

#include "counters.h"

void *simple_shared_count_worker(void *arg)
{
    uint64_t *counter = (uint64_t *)arg;

    for (uint64_t i = 0; i < DESIRED_TOTAL / NUM_THREADS; ++i)
    {
        ++(*counter);

        // prevent compiler inlining and other loop optimizations
        asm("");
    }

    return NULL;
}

uint64_t count_together_in_separate_threads()
{
    uint64_t counter = 0;
    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; ++i)
    {
        pthread_create(&threads[i], NULL, simple_shared_count_worker, &counter);
    }

    // wait for all threads to finish their work
    for (int i = 0; i < NUM_THREADS; ++i)
    {
        pthread_join(threads[i], NULL);
    }

    return counter;
}

