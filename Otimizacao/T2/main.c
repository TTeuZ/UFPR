#include <stdio.h>
#include "src/interface.h"
#include "src/heroes.h"
#include "src/optimize.h"

int main(int argc, char **argv)
{
    params_t params;
    heroes_t heroes;
    optimize_state_t optimize;

    read_params(argc, argv, &params);
    read_input(&heroes);

    init_optimize_state(&optimize, heroes.quantity);

    optimize_heroes(&heroes, &params, &optimize);
    show_results(&heroes, &optimize);

    heroes_destroy(&heroes);
    destroy_optimize_state(&optimize);
    return 0;
}