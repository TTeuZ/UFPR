#include <stdio.h>
#include <stdlib.h>
#include "linear_program.h"
#include "utils.h"

ProductionInput *read_production()
{
    ProductionInput *production;

    production = malloc(sizeof(ProductionInput));
    if (production == NULL || stdin == NULL)
        return NULL;

    fscanf(stdin, "%d %d", &production->productsQty, &production->compositesQty);

    production->productsValue = (float *)alloc_array(production->productsQty, sizeof(float));
    production->compositesCost = (float *)alloc_array(production->compositesQty, sizeof(float));
    production->compositesLimit = (float *)alloc_array(production->compositesQty, sizeof(float));
    production->productsRecipe = (float **)alloc_matrix(production->productsQty, production->compositesQty, sizeof(float));

    for (int i = 0; i < production->productsQty; ++i)
        fscanf(stdin, "%f", &production->productsValue[i]);

    for (int i = 0; i < production->compositesQty; ++i)
        fscanf(stdin, "%f %f", &production->compositesCost[i], &production->compositesLimit[i]);

    for (int i = 0; i < production->productsQty; ++i)
        for (int j = 0; j < production->compositesQty; ++j)
            fscanf(stdin, "%f", &production->productsRecipe[i][j]);

    return production;
}

void print_production(ProductionInput *production)
{
    printf("%d %d\n", production->productsQty, production->compositesQty);
    print_float_array(production->productsValue, production->productsQty);

    for (int i = 0; i < production->compositesQty; i++)
        printf("%f %f\n", production->compositesCost[i], production->compositesLimit[i]);

    for (int i = 0; i < production->productsQty; i++)
        print_float_array(production->productsRecipe[i], production->compositesQty);
}

void get_objective_function(ProductionInput *production)
{
    float compositesCost;

    printf("max: ");
    for (int i = 0; i < production->productsQty; i++)
    {
        printf("%fx%d", production->productsValue[i], i + 1);
        if (i != production->productsQty - 1)
            printf(" + ");
    }

    for (int i = 0; i < production->productsQty; i++)
    {
        compositesCost = 0;
        for (int j = 0; j < production->compositesQty; j++)
        {
            compositesCost += production->productsRecipe[i][j] * production->compositesCost[j];
        }
        printf(" - %fx%d", compositesCost, i + 1);
    }

    printf(";\n");
}

void get_constraints(ProductionInput *production)
{
    for (int i = 0; i < production->compositesQty; i++)
    {
        for (int j = 0; j < production->productsQty; j++)
        {
            printf("%fx%d", production->productsRecipe[j][i], j + 1);
            if (j != production->productsQty - 1)
                printf(" + ");
        }
        printf(" <= %f;\n", production->compositesLimit[i]);
    }

    for (int i = 0; i < production->productsQty; i++)
        printf("x%d >= 0;\n", i + 1);
}

void free_production(ProductionInput *production)
{
    free_matrix((void *)production->productsRecipe);
    free(production->productsValue);
    free(production->compositesCost);
    free(production->compositesLimit);
    free(production);
}