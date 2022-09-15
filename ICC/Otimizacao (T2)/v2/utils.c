#include "utils.h"

double timestamp (void) {
    struct timespec tp;
    clock_gettime(CLOCK_MONOTONIC_RAW, &tp);
    return((double)(tp.tv_sec*1.0e3 + tp.tv_nsec*1.0e-6));
}

double avx_register_sum (__m256d reg) {
    __m128d sum_aux_1, sum_aux_2, sum_final;

    sum_aux_1  = _mm256_castpd256_pd128(reg);
    sum_aux_2 = _mm256_extractf128_pd(reg, 1);
    sum_aux_1  = _mm_add_pd(sum_aux_1, sum_aux_2);
    sum_final = _mm_unpackhi_pd(sum_aux_1, sum_aux_1);
    return  _mm_cvtsd_f64(_mm_add_sd(sum_aux_1, sum_final));
}