#include <stdio.h>
#include <stdlib.h>
#include "heroes.h"

void *alloc_array(int length, int item_size)
{
    void *array = calloc(length, item_size);
    if (array == NULL)
    {
        perror("Error allocating array");
        exit(1);
    }
    return array;
}

void **alloc_matrix(int lines, int columns, int item_size)
{
    void **matrix = alloc_array(lines, sizeof(void *));
    matrix[0] = alloc_array(lines * columns, item_size);
    for (int i = 0; i < lines; i++)
        matrix[i] = matrix[0] + i * columns * item_size;
    return matrix;
}

int heroes_init(heroes_t *heroes, int quantity, int conflicts, int friendships)
{
    heroes->quantity = quantity;
    heroes->conflicts_qty = conflicts;
    heroes->friendships_qty = friendships;
    heroes->unavoided_conflicts = 0;

    heroes->conflicts = alloc_array(conflicts, sizeof(hero_pair_t));
    if (heroes->conflicts == NULL)
    {
        perror("Error allocating array");
        return -1;
    }

    heroes->friendships = alloc_array(friendships, sizeof(hero_pair_t));
    if (heroes->friendships == NULL)
    {
        perror("Error allocating array");
        return -1;
    }

    heroes->aux_matrix = (short int **)alloc_matrix(quantity, quantity, sizeof(short int));

    return 0;
}

void free_matrix(void **matrix)
{
    free(matrix[0]);
    free(matrix);
}

int heroes_destroy(heroes_t *heroes)
{
    if (heroes->conflicts)
        free(heroes->conflicts);

    if (heroes->friendships)
        free(heroes->friendships);

    if (heroes->aux_matrix)
        free_matrix((void **)heroes->aux_matrix);

    return 0;
}