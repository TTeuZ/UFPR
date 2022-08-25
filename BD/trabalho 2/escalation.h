#ifndef _ESCALATION_H_
#define _ESCALATION_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "schedule.h"

typedef struct escalations {
    schedule_t **list;
    int qtd;
} escalations_t;

/*!
    \brief Função de alocação inicial para a estrutura de escalonamentos
    \return Ponteiro de acesso em caso de sucesso. NULL em caso de falha de alocação
*/
escalations_t *alloc_escalations ();

/*!
    \brief Função que separa o 'agendamento mae' nos escalonamentos separados por commit
    \param schedule Ponteiro de acesso para o agendamento 
    \param escalations Ponteiro de acesso para a estrutura dos escalaonamentos
    \return EXIT_SUCCESS em caso de sucesso. EXIT_FAILURE em caso de falha de alocação
*/
int separete_schedule (schedule_t *schedule, escalations_t *escalations);

/*!
    \brief Funcao de limpeza de memoria alocada para os escalonamentos
    \param escalations Ponteiro de acesso para a estrutura dos escalaonamentos
*/
void destroy_escalations (escalations_t *escalations);
#endif