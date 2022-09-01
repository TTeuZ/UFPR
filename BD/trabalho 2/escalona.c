#include <stdio.h>
#include <stdlib.h>

#include "schedule.h"
#include "escalation.h"
#include "serializable.h"
#include "equivalentView.h"

int main () {
    schedule_t *schedule = NULL;
    escalations_t *escalations = NULL;
    int is_serializable, is_equivalent;
    int count, i_count;

    schedule_t *aux;
    int qtd;

    if (! (escalations = alloc_escalations ()))
        return EXIT_FAILURE;

    if (read_input_schedule (&schedule))
        return EXIT_FAILURE;

    if (separete_schedule (schedule, escalations))
        return EXIT_FAILURE;

    for (count = 0; count < escalations->qtd; count++) {
        aux = escalations->list[count];
        qtd = aux->transactions_qtd;

        is_serializable = check_serializable (aux);
        is_equivalent = check_equivalence (aux);

        printf ("%d ", count + 1);
        for (i_count = 0; i_count < qtd; i_count++)
            printf ("%d%c", aux->transactions_ids[i_count], (i_count + 1) == qtd ? ' ' : ',');

        if (is_serializable) printf ("SS ");
        else printf ("NS ");

        if (is_equivalent) printf ("SV");
        else printf ("NV");

        if (count + 1 != escalations->qtd) printf ("\n");
    }

    destroy_escalations (escalations);
    free (schedule);
    return EXIT_SUCCESS;
}