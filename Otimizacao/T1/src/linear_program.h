#ifndef __LINEAR_PROGRAM__
#define __LINEAR_PROGRAM__

typedef struct ProductionInput
{
    int productsQty, compositesQty;
    float *compositesCost;
    float *compositesLimit;
    float *productsValue;
    float **productsRecipe;
} ProductionInput;

ProductionInput *read_production();

void print_production(ProductionInput *production);

void get_objective_function(ProductionInput *production);

void get_constraints(ProductionInput *production);

void free_production(ProductionInput *production);

#endif