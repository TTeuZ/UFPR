#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "interface.h"

void read_params(int argc, char **argv, params_t *params)
{
    int option;

    params->custom_bound = 1;
    params->feasibility = 1;
    params->optimization = 1;

    while ((option = getopt(argc, argv, "afo")) != -1)
    {
        switch (option)
        {
        case 'a':
            params->custom_bound = 0;
            break;
        case 'f':
            params->feasibility = 0;
            break;
        case 'o':
            params->optimization = 0;
            break;
        default:
            exit(-1);
            break;
        }
    }
}

void read_input(heroes_t *heroes)
{
    int quantity, conflicts, friendships;
    fscanf(stdin, "%d %d %d", &quantity, &conflicts, &friendships);

    heroes_init(heroes, quantity, conflicts, friendships);

    for (int i = 0; i < heroes->conflicts_qty; ++i)
        fscanf(stdin, "%d %d", &heroes->conflicts[i].hero1, &heroes->conflicts[i].hero2);

    for (int i = 0; i < heroes->friendships_qty; ++i)
        fscanf(stdin, "%d %d", &heroes->friendships[i].hero1, &heroes->friendships[i].hero2);
}

void show_results(heroes_t *heroes, optimize_state_t *optimize)
{
    int first_hero_group = optimize->opt_solution[0];

    fprintf(stdout, "%d\n", optimize->opt_value);

    for (int i = 0; i < heroes->quantity; i++)
        if (optimize->opt_solution[i] == first_hero_group)
            fprintf(stdout, "%d ", i + 1);
    fprintf(stdout, "\n");

    fprintf(stderr, "Tempo: %fs\n", optimize->time);
    fprintf(stderr, "Nodos: %d\n", optimize->nodes);
}