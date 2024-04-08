#include "counters.h"

uint64_t count_in_main_thread()
{
    uint64_t counter = 0;
    for (uint64_t i = 0; i < DESIRED_TOTAL; ++i)
    {
        ++counter;

        // prevent compiler inlining and other loop optimizations
        asm("");
    }

    return counter;
}
