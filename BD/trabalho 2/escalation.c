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
    operation_t *aux, *next;
    int open_qtd, *open_transactions;
    int count, o_count;

    aux = schedule->start;
    count = open_qtd = 0;

    if (! (open_transactions = malloc (sizeof (int) * schedule->transactions_qtd)))
        return EXIT_FAILURE;

    while (count < schedule->size) {
        for (o_count = 0; o_count < schedule->transactions_qtd; o_count++)
            open_transactions[o_count] = 0;

        if (escalations->qtd == 0) {
            if (! (escalations->list = malloc (sizeof (schedule_t) * (escalations->qtd + 1))))
                return EXIT_FAILURE;
        } else {
            if (! (escalations->list = realloc (escalations->list, sizeof (schedule_t) * (escalations->qtd + 1))))
                return EXIT_FAILURE;
        }

        if (! (escalations->list[escalations->qtd] = alloc_schedule ()))
            return EXIT_FAILURE;

        do {
            if (aux->op_type != 'C' && open_transactions[aux->transaction_id - 1] != 1) {
                open_transactions[aux->transaction_id - 1] = 1;
                open_qtd++;
            }

            if (aux->op_type == 'C' && open_transactions[aux->transaction_id - 1] == 1) {
                open_transactions[aux->transaction_id - 1] = 0;
                open_qtd--;
            }

            next = aux->next;
            aux->next = NULL;
            aux->prev = NULL;
            add_schedule_operation (escalations->list[escalations->qtd], aux);
            if (aux->op_type == 'C') escalations->list[escalations->qtd]->transactions_qtd++;

            aux = next;
            count++;
        } while (count < schedule->size && open_qtd != 0);

        if (get_ids (escalations->list[escalations->qtd]))
            return EXIT_FAILURE;

        escalations->list[escalations->qtd]->size++;
        escalations->qtd++;
    }
    
    free (open_transactions);
    return EXIT_SUCCESS;
}

void destroy_escalations (escalations_t *escalations) {
    int count;
    
    for (count = 0; count < escalations->qtd; count++) 
        destroy_schedule (escalations->list[count]);
    
    free (escalations->list);
    free (escalations);
}