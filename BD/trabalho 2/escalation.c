#include "escalation.h"

escalations_t *alloc_escalations () {
    escalations_t *escalations;

    if (! (escalations = malloc (sizeof (escalations_t))))
        return NULL;
    escalations->list = NULL;
    escalations->qtd = 0;
    return escalations;
}

int separete_schedule (schedule_t *schedule, escalations_t *escalations) {
    schedule_t *temp;
    operation_t *aux = schedule->start;
    int open_qtd = 0, count = 0;

    if (! (temp = alloc_schedule ()))
        return EXIT_FAILURE;

    while (count < schedule->size) {
        do {
            
        } while (count < schedule->size && open_qtd != 0);
    }
}