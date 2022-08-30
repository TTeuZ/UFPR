#include "serializable.h"

int check_serializable (schedule_t *schedule) {
    operation_t *aux, *last;
    graph_t *graph;
    int is_serializable;

    is_serializable = true;
    aux = schedule->start;

    if (! (graph = alloc_graph (schedule->transactions_qtd)))
        return -1;
    

    while (aux) {
        last = aux->prev;
        while (last) {
            if (last->transaction_id != aux->transaction_id) {
                if (aux->op_type == 'W' && last->op_type == 'R')
                    insert_edge (graph, aux->transaction_id - 1, last->transaction_id - 1);
                    // printf ("W(X) depois de R(X) -- insere aresta de %d para %d\n", aux->transaction_id, last->transaction_id);
                if (aux->op_type == 'R' && last->op_type == 'W') 
                    insert_edge (graph, aux->transaction_id - 1, last->transaction_id - 1);
                    // printf ("R(X) depois de W(X) -- insere aresta de %d para %d\n", aux->transaction_id, last->transaction_id);
                if (aux->op_type == 'W' && last->op_type == 'W') 
                    insert_edge (graph, aux->transaction_id - 1, last->transaction_id - 1);
                    // printf ("W(X) depois de W(X) -- insere aresta de %d para %d\n", aux->transaction_id, last->transaction_id);
            }
            last = last->prev;
        }
        aux = aux->next;
    }

    int count, count2;
    for (count = 0; count < graph->vertices_qtd; count++) {
        printf ("%2d: ", count);
        for (count2 = 0; count2 < graph->vertices_qtd; count2++) {
            if (graph->adj_matrix[count][count2] == 1)
                printf (" %2d", count2);
        }
        printf ("\n");
    }

    return is_serializable;
}