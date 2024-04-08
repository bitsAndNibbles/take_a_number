#include <pthread.h>

#include "counters.h"

void *get_subtotal(void *arg)
{
    uint64_t *local_counter = arg;
    *local_counter = 0;

    for (uint64_t i = 0; i < DESIRED_TOTAL / NUM_THREADS; ++i)
    {
        ++*local_counter;

        // prevent compiler inlining and other loop optimizations
        asm("");
    }

    return arg;
}

uint64_t divide_up_counting_and_summarize()
{
    // keep track of each thread's ID and, when the thread exits,
    // the final subtotal it produced so that we may summarize it
    // with the others.
    struct thread_info
    {
        pthread_t thread_id;
        uint64_t subtotal;
    };
    
    uint64_t total_count = 0;

    struct thread_info threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; ++i)
    {
        pthread_create(&threads[i].thread_id,
            NULL,
            get_subtotal,
            (void *)(&threads[i].subtotal));
    }

    // accumulate total count by summing each thread's work result
    for (int i = 0; i < NUM_THREADS; ++i)
    {
        pthread_join(threads[i].thread_id, NULL);
        
        total_count += threads[i].subtotal;
    }

    return total_count;
}

