#ifndef __STEPS_H__
#define __STEPS_H__

#include "stdio.h"
#include <stdlib.h>

typedef struct steps {
    int line;
    int pivot;
} steps_t;
typedef struct pivot_steps {
    steps_t **list;
    int qtd;
} pivot_steps_t;

/*!
    \brief Aloca espaço para a struct de passos de pivotamento
    \returns Ponteiro de acesso para a estrutura steps em caso de sucesso. Null em caso de falha
*/
pivot_steps_t *alloc_steps ();

/*!
    \brief Libera o espaço alocado para o pivot_steps
    \param steps Ponteiro de acesso para lista de passos
*/
void free_steps (pivot_steps_t *steps);

#endif