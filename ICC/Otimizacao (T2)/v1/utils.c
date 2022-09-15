#include "utils.h"

double timestamp (void) {
    struct timespec tp;
    clock_gettime(CLOCK_MONOTONIC_RAW, &tp);
    return((double)(tp.tv_sec*1.0e3 + tp.tv_nsec*1.0e-6));
}