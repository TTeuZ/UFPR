#include "serializable.h"

int check_serializable (schedule_t *schedule) {
    operation_t *aux, *last;
    graph_t *graph;
    int is_serializable, lower_id;

    is_serializable = true;
    aux = schedule->start;

    if (! (graph = alloc_graph (schedule->transactions_qtd)))
        return -1;
    
    lower_id = schedule->transactions_ids[0];

    while (aux) {
        last = aux->prev;
        while (last) {
            if (last->transaction_id != aux->transaction_id && (last->attribute == aux->attribute)) {
                if (aux->op_type == 'W' && last->op_type == 'R')
                    insert_edge (graph, aux->transaction_id - lower_id, last->transaction_id - lower_id);
                if (aux->op_type == 'R' && last->op_type == 'W') 
                    insert_edge (graph, aux->transaction_id - lower_id, last->transaction_id - lower_id);
                if (aux->op_type == 'W' && last->op_type == 'W') 
                    insert_edge (graph, aux->transaction_id - lower_id, last->transaction_id - lower_id);
            }
            last = last->prev;
        }
        aux = aux->next;
    }

    is_serializable = has_cycle (graph);

    destroy_graph (graph);
    return !is_serializable;
}