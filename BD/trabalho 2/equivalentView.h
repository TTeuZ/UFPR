#ifndef _EQUIVALENT_VIEW_H_
#define _EQUIVALENT_VIEW_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "schedule.h"
#include "utils.h"

typedef struct reads {
    int read_t;
    int write_t;
} reads_t;

/*!
    \brief Função que checa se o escalonamento é equivalente
    \param schedule Ponteiro para um escalonamento (Agendamento)
    \return True em caso de ser equivalente. Falso em caso se não ser equivalente
*/
int check_equivalence (schedule_t *schedule);

#endif