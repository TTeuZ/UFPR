#include "schedule.h"

schedule_t *alloc_schedule () {
    schedule_t *schedule;

    if (! (schedule = malloc (sizeof (schedule_t))))
        return NULL;
    
    schedule->size = 0;
    schedule->transactions_qtd = 0;
    schedule->transactions_ids = NULL;
    schedule->start = NULL;
    schedule->end = NULL;
    return schedule;
}

operation_t *create_operation (int timestamp, int transaction_id, char op_type, char attribute) {
    operation_t *operation;

    if (! (operation = malloc (sizeof (operation_t))))
        return NULL;
    
    operation->timestamp = timestamp;
    operation->transaction_id = transaction_id;
    operation->op_type = op_type;
    operation->attribute = attribute;
    operation->next = NULL;
    operation->prev = NULL;
    return operation;
}

void add_schedule_operation (schedule_t *schedule, operation_t *operation) {
    if (! schedule->start && ! schedule->end) {
        schedule->start = schedule->end = operation;
        return;
    }

    schedule->end->next = operation;
    operation->prev = schedule->end;
    schedule->end = operation;
    schedule->size++;
}

int read_input_schedule (schedule_t **schedule) {
    schedule_t *temp;
    operation_t *operation = NULL;
    int timestamp, transaction_id;
    char op_type, attribute;

    if (! (temp = alloc_schedule ()))
        return EXIT_FAILURE;

    fscanf (stdin, "%d %d %c %c", &timestamp, &transaction_id, &op_type, &attribute);
    while (! feof (stdin)) {
        if (! (operation = create_operation (timestamp, transaction_id, op_type, attribute)))
            return EXIT_FAILURE;

        add_schedule_operation (temp, operation);
        if (operation->op_type == 'C') temp->transactions_qtd++;

        fscanf (stdin, "%d %d %c %c", &timestamp, &transaction_id, &op_type, &attribute);
    }
    temp->size++;
    *schedule = temp;
    return EXIT_SUCCESS;
}

int get_ids (schedule_t *schedule) {
    operation_t *aux = schedule->start;
    int count = 0, i_count;

    if (! (schedule->transactions_ids = malloc (sizeof (int) * schedule->transactions_qtd)))
        return EXIT_FAILURE;
    memset (schedule->transactions_ids, 0, sizeof (int) * schedule->transactions_qtd);

    while (aux) {
        if (! includes (aux->transaction_id, schedule->transactions_qtd, schedule->transactions_ids)) {
            if (count == 0) schedule->transactions_ids[count] = aux->transaction_id;
            else {
                i_count = count;
                while (i_count != 0 && aux->transaction_id < schedule->transactions_ids[i_count - 1]) {
                    schedule->transactions_ids[i_count] = schedule->transactions_ids[i_count - 1];
                    i_count--;
                }
                schedule->transactions_ids[i_count] = aux->transaction_id;
            }
            count++;
        }
        aux = aux->next;
    }
    return EXIT_SUCCESS;
}

void destroy_schedule (schedule_t *schedule) {
    operation_t *temp;
    temp = schedule->start;

    while (temp) {
        schedule->start = temp->next;
        free (temp);
        temp = schedule->start;
    }
    free (schedule->transactions_ids);
    free (schedule);
}