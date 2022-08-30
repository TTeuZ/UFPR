#ifndef _EQUIVALENT_VIEW_H_
#define _EQUIVALENT_VIEW_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "schedule.h"
#include "utils.h"

/*!
    \brief Função que gera a visão atual do escalonamento
    \param schedule Ponteiro para um escalonamento (Agendamento)
    \param vision Ponteiro para a visão resultante (retorno)
    \param ids Array dos ids do escalonamento
    \return EXIT_SUCCESS em caso de sucesso. EXIT_FAILURE em caso de falha de alocação
*/
int generate_vision (schedule_t *schedule, schedule_t **vision, int *ids);

/*!
    \brief Função que checa se o escalonamento é equivalente
    \param schedule Ponteiro para um escalonamento (Agendamento)
    \return True em caso de ser equivalente. Falso em caso se não ser equivalente
*/
int check_equivalence (schedule_t *schedule);

#endif