#include "steps.h"

pivot_steps_t *alloc_steps () {
    pivot_steps_t *pivot_steps;

    if ((pivot_steps = malloc (sizeof (pivot_steps_t)))) {
        pivot_steps->list = NULL;
        pivot_steps->qtd = 0;
        return pivot_steps;
    } else return NULL;
}

void free_steps (pivot_steps_t *steps) {
    int count;
    for (count = 0; count < steps->qtd; count++) 
        free (steps->list[count]);
    free (steps->list);
    free (steps);
}