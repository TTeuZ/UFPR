#ifndef __OPTIMIZE__
#define __OPTIMIZE__

typedef struct optimize_state_t optimize_state_t;

#include "interface.h"
#include "heroes.h"

typedef struct optimize_state_t
{
    int *cur_solution;
    int *opt_solution;
    int opt_value;
    int nodes;
    double time;
} optimize_state_t;

/*!
    \brief Branch and bound function
    \param heroes Pointer to the heroes structure
    \param params Pointer to the params structure
*/
int optimize_heroes(heroes_t *heroes, params_t *params, optimize_state_t *optimize);

/*!
    \brief Allocate the memory for the internal structures of the optimize structure
    \param optimize Pointer to the optimize structure
    \param quantity Size of the arrays
*/
void init_optimize_state(optimize_state_t *optimize, int quantity);

/*!
    \brief Free the memory allocated for the optimize structure
    \param optimize Pointer to the optimize structure
*/
void destroy_optimize_state(optimize_state_t *optimize);
#endif