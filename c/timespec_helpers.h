#ifndef TIMESPEC_HELPERS_H
#define TIMESPEC_HELPERS_H

#include <time.h> // clock()

double duration_s(struct timespec *start, struct timespec *end);

#endif // TIMESPEC_HELPERS_H
