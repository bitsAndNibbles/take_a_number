#include <inttypes.h> // PRIu64
#include <stdint.h> // uint64_t
#include <stdio.h> // printf()
#include <time.h> // clock()

#include "counters.h"
#include "timespec_helpers.h"


const uint64_t DESIRED_TOTAL = 1000000000L;
const int NUM_THREADS = 10;


int main()
{
    struct timespec clock_start, clock_end;
    double clock_time_s;

    clock_t cpu_start, cpu_end;
    double cpu_time_s;

    timespec_get(&clock_start, TIME_UTC);
    cpu_start = clock();

    /**
     *                                       perf on Intel Core Ultra 7 laptop
     * method                                with 1000000000L and 10 threads
     *                                       [  wall clock  |  cpu time  ]
     * count_in_main_thread                  [   1.15 s     |   1.15 s   ]
     * count_together_in_separate_threads    [   1.61 s     |   15.6 s   ]
     * take_turns_counting                   [   71.4 s     |   560. s   ]
     * divide_up_counting_and_summarize      [   0.68 s     |   5.71 s   ]
     */
    uint64_t counter = divide_up_counting_and_summarize();

    cpu_end = clock();
    timespec_get(&clock_end, TIME_UTC);

    clock_time_s = duration_s(&clock_start, &clock_end);
    cpu_time_s = (double)(cpu_end - cpu_start) / CLOCKS_PER_SEC;

    printf("Wall clock time: %.6fs, CPU time: %.6fs\n",
        clock_time_s,
        cpu_time_s);

    if (counter == DESIRED_TOTAL)
    {
        printf("SUCCESS!\n");
    }
    else
    {
        printf(
            "FAILURE! Expected %" PRIu64 ", got %" PRIu64
            ", a difference of %" PRIu64 ".\n",
            DESIRED_TOTAL,
            counter,
            DESIRED_TOTAL - counter);
    }

    return 0;
}
