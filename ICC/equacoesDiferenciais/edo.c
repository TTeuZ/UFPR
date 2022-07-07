#include <stdio.h>
#include <stdlib.h>

#include "edo.h"

edo_h *aloc_edo () {
    edo_h *edo;
    if (! (edo = malloc (sizeof (edo_h)))) 
        return NULL;
    else return edo;
}

edo_h *init_edo (double s_interval, double f_interval, double y_s_interval, double y_f_interval, int n) {
    edo_h *edo;
    if ((edo = malloc (sizeof (edo_h)))) {
        edo->n = n;
        edo->s_interval = s_interval;
        edo->f_interval = f_interval;
        edo->y_s_interval = y_s_interval;
        edo->y_f_interval = y_f_interval;
        return edo;
    } else return NULL;
}