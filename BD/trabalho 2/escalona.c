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

    if (separete_schedule (schedule, escalations))
        return EXIT_FAILURE;

    int count;
    operation_t *aux;

    for (count = 0; count < escalations->qtd; count++) {
        printf ("Escalonamento %d\n", count);
        aux = escalations->list[count]->start;
        while (aux != NULL) {
            printf ("%d %d %c %c\n", aux->timestamp, aux->transaction_id, aux->op_type, aux->attribute);
            aux = aux->next;
        }
        printf ("------------------------\n");
    }

    destroy_escalations (escalations);
    free (schedule);
    return EXIT_SUCCESS;
}