#ifndef __INTERFACE__
#define __INTERFACE__

typedef struct params_t params_t;

#include "heroes.h"
#include "optimize.h"

typedef struct params_t
{
    int feasibility, optimization, custom_bound;
} params_t;

/*!
    \brief Read argv keeping the parameters sent
    \param argc the number of arguments
    \param argv the array of arguments
    \param params Pointer to the params_t structure
*/
void read_params(int argc, char **argv, params_t *params);

/*!
    \brief Read the input file
    \param heroes Pointer to the heroes structure
*/
void read_input(heroes_t *heroes);

/*!
    \brief Print out the result
    \param optimize Pointer to the optimize_state_t structure
*/
void show_results(heroes_t *heroes, optimize_state_t *optimize);

#endif