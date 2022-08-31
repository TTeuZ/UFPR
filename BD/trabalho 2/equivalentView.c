#include "equivalentView.h"

//------------------------------------- Funções interanas -------------------------------------
operation_t *find_last_write (schedule_t *schedule) {
    operation_t *aux;
    aux = schedule->end;
    while (aux) {
        if (aux->op_type == 'W') return aux;
        aux = aux->prev;
    }
    return aux;
}


void swap (int *ids, int font, int target) {
    int temp;
    temp = ids[font];
    ids[font] = ids[target];
    ids[target] = temp;
}
/*!
    \brief Função que pega a proxima permutação do array de ids
    \param ids Vetor de ids da transação
    \param left Posição mais a esquerda da permutação atual
    \param right Posição mais a direita da permutação atual
*/
void next_permutation (int *ids, int *left, int *right) {
    int count;
    if (*left == *right) {
        *left = 1;
        swap (ids, 0, *right);
        return;
    } 

    for (count = *left; count <= *right; count++) 
        swap (ids, *left, count);
    *left = *left + 1;
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
    int possible_sequences, count, left, right;
    int is_equivalent;
    int *ids;

    // ------- estruturas auxiliares de verificação -------
    schedule_t *vision = NULL;
    operation_t *last_write, *vision_last_write, *aux;

    last_write = find_last_write (schedule);
    // ------- estruturas auxiliares de verificação -------

    // ------- Array de ids para a as permutações -------
    if (! (ids = calloc (schedule->transactions_qtd, sizeof (int))))
        return EXIT_FAILURE;
    
    memset (ids, 0, sizeof (int) * (schedule->transactions_qtd));
    for (count = 0; count < schedule->transactions_qtd; count++)
        ids[count] = schedule->transactions_ids[count];

    left = 1;
    right = schedule->transactions_qtd - 1;
    possible_sequences = fat (schedule->transactions_qtd);
    // ------- Array de ids para a as permutações -------

    

    // for (count = 0; count < possible_sequences; count++) {
    //     generate_vision (schedule, &vision, ids);
    //     is_equivalent = true;


    //             aux = vision->start;
    //     while (aux != NULL) {
    //         printf ("%d %d %c %c\n", aux->timestamp, aux->transaction_id, aux->op_type, aux->attribute);
    //         aux = aux->next;
    //     }
    //     printf ("--------------------------------\n");
    //     // printf ("Tamanho: %d - qtd de transaçoes %d\n", vision->size, vision->transactions_qtd);



    //     // vision_last_write = find_last_write (vision);

    //     // if (last_write->transaction_id != vision_last_write->transaction_id)
    //     //     is_equivalent = false;

    //     destroy_schedule (vision);
    //     next_permutation (ids, &left, &right);
    // }
    

    free (ids);
    return EXIT_SUCCESS;
}