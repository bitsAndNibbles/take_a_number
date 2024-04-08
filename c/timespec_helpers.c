#include "timespec_helpers.h"

double duration_s(struct timespec *start, struct timespec *end)
{
    struct timespec diff =
    {
        .tv_sec = end->tv_sec - start->tv_sec,
        .tv_nsec = end->tv_nsec - start->tv_nsec
    };
    if (diff.tv_nsec < 0)
    {
        diff.tv_nsec += 1000000000;
        --diff.tv_sec;
    }

    return (double)(diff.tv_sec + (diff.tv_nsec / 1e9));
}
