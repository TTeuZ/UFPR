#include "equivalentView.h"

//------------------------------------- Funções interanas -------------------------------------
/*!
    \brief Função que pega a proxima permutação do array de ids
    \param ids Vetor de ids da transação
    \param left Posição mais a esquerda da permutação atual
    \param right Posição mais a direita da permutação atual
*/
void next_permutation (int *ids, int *left, int *right) {

}

//------------------------------------- Funções interanas -------------------------------------

int generate_vision (schedule_t *schedule, schedule_t **vision, int *ids) {
    operation_t *aux, *operation;
    schedule_t *temp;
    int count;

    if (! (temp = alloc_schedule ()))
        return EXIT_FAILURE;
    temp->transactions_qtd = schedule->transactions_qtd;
    
    for (count = 0; count < schedule->transactions_qtd; count++) {
        aux = schedule->start;
        while (aux) {
            if (aux->transaction_id == ids[count] && aux->op_type != 'C') {
                if (! (operation = create_operation (aux->timestamp, aux->transaction_id, aux->op_type, aux->attribute)))
                    return EXIT_FAILURE;
                add_schedule_operation (temp, operation);
            }
            aux = aux->next;
        }
    }
    temp->size++;
    *vision = temp;
    return EXIT_SUCCESS;
}

int check_equivalence (schedule_t *schedule) {
    schedule_t *vision = NULL;
    operation_t *aux;
    int possible_sequences, count, left, right;
    int *ids;

    if (! (ids = calloc (schedule->transactions_qtd, sizeof (int))))
        return EXIT_FAILURE;
    
    memset (ids, 0, sizeof (int) * (schedule->transactions_qtd + 1));
    for (count = 0; count < schedule->transactions_qtd; count++)
        ids[count] = schedule->transactions_ids[count];

    left = 0;
    right = schedule->transactions_qtd - 1;
    possible_sequences = fat (schedule->transactions_qtd);

    for (count = 0; count < possible_sequences; count++) {
        generate_vision (schedule, &vision, ids);

        aux = vision->start;
        while (aux != NULL) {
            printf ("%d %d %c %c\n", aux->timestamp, aux->transaction_id, aux->op_type, aux->attribute);
            aux = aux->next;
        }
        printf ("Tamanho: %d - qtd de transaçoes %d\n", vision->size, vision->transactions_qtd);



        destroy_schedule (vision);
        next_permutation (ids, &left, &right);
    }
    

    free (ids);
    return EXIT_SUCCESS;
}