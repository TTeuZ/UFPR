#include "equivalentView.h"

//------------------------------------- Funções interanas -------------------------------------
/*!
    \brief Função que gera o escalonamento de visão de acordo com a seguencia do array ids
    \param schedule Ponteiro para o escalonamento de Origem
    \param vision Ponteiro para o escalonamento que vai receber a visão
    \param ids Array de ids para a construção da visão
    \return EXIT_FAILURE em caso de falha de alocação. EXIT_SUCCESS em caso de sucesso.
*/
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
            if (aux->transaction_id == ids[count]) {
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

/*!
    \brief Função que encontra as ultimas escritas do escalonamento enviado
    \param schedule Ponteiro para o escalonamento
    \param last_write Ponteiro para o vetor de escritas
    \param lower_id Inteiro que indica o valor do menor id (para quesitos de acesso ao array)
*/
void find_last_write (schedule_t *schedule, int *last_writes, int lower_id) {
    operation_t *aux;
    aux = schedule->end;
    while (aux) {
        if (aux->op_type == 'W' && ! includes (aux->attribute, schedule->transactions_qtd, last_writes)) 
            last_writes[aux->transaction_id - lower_id] = aux->attribute;
        aux = aux->prev;
    }
}

/*!
    \brief Função que encontra todas as relações de leitura -> escrita do escaolanemtno enviado
    \param schedule Ponteiro para o escalonamento
    \param reads Ponteiro par ao vetor de relações
*/
void get_all_reads_relations (schedule_t *schedule, reads_t *reads) {
    operation_t *aux, *prev;
    int count = 0, found;

    aux = schedule->start;
    while (aux) {
        if (aux->op_type == 'R') {
            prev = aux->prev;
            found = 0;
            while (prev && ! found) {
                if (prev->op_type == 'W' && (aux->attribute == prev->attribute)) {
                    reads[count].write_t = prev->transaction_id;
                    reads[count].read_t = aux->transaction_id;
                    found = 1;
                    count++;
                }
                prev = prev->prev;
            }
        }
        aux = aux->next;
    }
}

/*!
    \brief Função que troca os ids de duas posições do array
    \param ids Array de ids para a construção da visão
    \param font Posição de troca do id
    \param target Posição de troca do id
*/
void swap (int *ids, int font, int target) {
    int temp;
    temp = ids[font];
    ids[font] = ids[target];
    ids[target] = temp;
}

/*!
    \brief Função que gera as visões do agendamento e verifica se a visão é equivalente ou não.
    As visões são baseadas nas permutações do array de ids.
    \return true para caso encontre uma visão equivalente. falso para caso não exista visão equivalente
*/
int verify_visions (schedule_t *schedule, int *ids, int *last_writes, reads_t *reads, int size, int lower_id) {
    schedule_t *vision = NULL;
    int count, is_equivalent;
    int *vision_last_writes;
    reads_t *vision_reads;

    if (size == 0) {
        is_equivalent = true;
        generate_vision (schedule, &vision, ids);

        // ------- ultimas escritas do agentamento 'visão' -------
        if (! (vision_last_writes = calloc (schedule->transactions_qtd, sizeof (int))))
            return EXIT_FAILURE;

        memset (vision_last_writes, 0, sizeof (int) * (schedule->transactions_qtd));
        find_last_write (vision, vision_last_writes, lower_id);

        for (count = 0; count < schedule->transactions_qtd; count++)
            if (last_writes[count] != vision_last_writes[count]) 
                is_equivalent = false;
        // ------- ultimas escritas do agentamento 'visão' -------

        // ------- relações das demais escritas do agentamento 'visão' -------
        if (! (vision_reads = calloc (schedule->size, sizeof (reads_t))))
            return EXIT_FAILURE;

        for (count = 0; count < schedule->size; count++) 
            vision_reads[count].read_t = vision_reads[count].write_t = 0;
        get_all_reads_relations (vision, vision_reads);

        for (count = 0; count < schedule->size; count++) {
            if (reads[count].write_t != vision_reads[count].write_t && 
                reads[count].read_t != vision_reads[count].read_t) 
                is_equivalent = false;
        }
        // ------- relações das demais escritas do agentamento 'visão' -------

        free (vision_reads);
        free (vision_last_writes);
        destroy_schedule (vision);
        return is_equivalent;
    } else {
        if (verify_visions (schedule, ids, last_writes, reads, size - 1, lower_id)) return true;
        for (count = 0; count < size; count++) {
            swap (ids, count, size);
            if (verify_visions (schedule, ids, last_writes, reads, size - 1, lower_id)) return true;
            swap (ids, count, size);
        }
        return false;
    }
}

//------------------------------------- Funções internas -------------------------------------

int check_equivalence (schedule_t *schedule) {
    int is_equivalent, count;
    int *ids, *last_writes;
    int lower_id;
    reads_t *reads;

    lower_id = schedule->transactions_ids[0];

    // ------- ultimas escritas do agentamento 'original' -------
    if (! (last_writes = calloc (schedule->transactions_qtd, sizeof (int))))
        return EXIT_FAILURE;

    memset (last_writes, 0, sizeof (int) * (schedule->transactions_qtd));
    find_last_write (schedule, last_writes, lower_id);
    // ------- ultimas escritas do agentamento 'original' -------

    // ------- relações das demais escritas do agentamento 'original' -------
    if (! (reads = calloc (schedule->size, sizeof (reads_t))))
        return EXIT_FAILURE;

    for (count = 0; count < schedule->size; count++) 
        reads[count].read_t = reads[count].write_t = 0;
    get_all_reads_relations (schedule, reads);
    // ------- relações das demais escritas do agentamento 'original' -------

    // ------- Array de ids para a as permutações -------
    if (! (ids = calloc (schedule->transactions_qtd, sizeof (int))))
        return EXIT_FAILURE;
    
    memset (ids, 0, sizeof (int) * (schedule->transactions_qtd));
    for (count = 0; count < schedule->transactions_qtd; count++)
        ids[count] = schedule->transactions_ids[count];

    // ------- Array de ids para a as permutações -------

    is_equivalent = verify_visions (schedule, ids, last_writes, reads, schedule->transactions_qtd - 1, lower_id);

    free (ids);
    free (reads);
    free (last_writes);
    return is_equivalent;
}