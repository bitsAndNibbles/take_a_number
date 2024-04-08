#ifndef COUNTERS_H
#define COUNTERS_H


#include <stdint.h> // uint64_t

extern const uint64_t DESIRED_TOTAL;
extern const int NUM_THREADS;

uint64_t count_in_main_thread();
uint64_t count_together_in_separate_threads();
uint64_t take_turns_counting();
uint64_t divide_up_counting_and_summarize();


#endif // COUNTERS_H
