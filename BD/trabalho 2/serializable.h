#ifndef _SERIAZABLE_H_
#define _SERIAZABLE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "schedule.h"
#include "graphs.h"
#include "utils.h"

/*!
    \brief Função que checa se o escalonamento é serializavel por conflito
    \param schedule Ponteiro para um escalonamento (Agendamento)
    \return True em caso de ser serializavel Falso em caso se não ser serializavel
*/
int check_serializable (schedule_t *schedule);

#endif