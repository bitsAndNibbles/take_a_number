#include <pthread.h>

#include "counters.h"

typedef struct
{
    pthread_mutex_t mutex;
    uint64_t counter;
} shared_state;

void *count_with_critical_section(void *arg)
{
    shared_state *state = arg;

    for (uint64_t i = 0; i < DESIRED_TOTAL / NUM_THREADS; ++i)
    {
        // protect reading and writing to counter; this is our critical section
        pthread_mutex_lock(&state->mutex);
        ++(state->counter);
        pthread_mutex_unlock(&state->mutex);

        // prevent compiler inlining and other loop optimizations
        asm("");
    }

    return NULL;
}

uint64_t take_turns_counting()
{
    shared_state state;
    state.counter = 0;

    pthread_t threads[NUM_THREADS];

    pthread_mutex_init(&state.mutex, NULL);

    for (int i = 0; i < NUM_THREADS; ++i)
    {
        pthread_create(&threads[i],
            NULL,
            count_with_critical_section,
            (void *)(&state));
    }

    // wait for all threads to finish their work
    for (int i = 0; i < NUM_THREADS; ++i)
    {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&state.mutex);

    return state.counter;
}

