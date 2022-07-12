#include <stdio.h>
#include <stdlib.h>

#include "edo.h"

edo_h *aloc_edo () {
    edo_h *edo;
    if ((edo = malloc (sizeof (edo_h)))) 
        return edo;
    else return NULL;
}

void set_edo_conditions (edo_h *edo, double a, double b, double ya, double yb) {
    edo->a = a;
    edo->b = b;
    edo->ya = ya;
    edo->yb = yb;
}

void set_edo_coefficients (edo_h *edo, double (*p) (double), double (*q) (double), double (*r) (double)) {
    edo->p = p;
    edo->q = q;
    edo->r = r;
}

void set_edo_mesh (edo_h *edo, int n) {
    edo->n = n;
}