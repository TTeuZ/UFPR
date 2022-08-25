#include <stdio.h>
#include <stdlib.h>

#include "schedule.h"
#include "escalation.h"

int main () {
    schedule_t *schedule = NULL;
    escalations_t *escalations = NULL;

    if (! (escalations = alloc_escalations ()))
        return EXIT_FAILURE;

    if (read_input_schedule (&schedule))
        return EXIT_FAILURE;

    // operation_t *aux;

    // aux = schedule->start;

    // while (aux != NULL) {
    //     printf ("%d %d %c %c\n", aux->timestamp, aux->transaction_id, aux->op_type, aux->attribute);
    //     aux = aux->next;
    // }

    destroy_schedule (schedule);
    return EXIT_SUCCESS;
}