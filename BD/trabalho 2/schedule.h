#ifndef _SCHEDULE_H_
#define _SCHEDULE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

typedef struct operation {
    int transaction_id;
    char op_type;
    char attribute;
    int timestamp;
    struct operation *next;
    struct operation *prev;
} operation_t;

typedef struct schedule {
    int size;
    int transactions_qtd;
    int *transactions_ids;
    operation_t *start;
    operation_t *end;
} schedule_t;

/*!
    \brief Função que aloca a memória para a estrutura do agendamento
    \return Ponteiro de acesso para a estrutura em caso de sucesso. NULL em caso de falha
*/
schedule_t *alloc_schedule ();

/*!
    \brief Função que cria uma operação
    \param timestamp Timestamp da operação
    \param transaction_id Id da transação da operação
    \param op_type Tipo da operação que esta sendo feita
    \param attribute Atributo sobre o qual esta sendo feita a operação
    \return EXIT_SUCCESS em caso de sucesso. EXIT_FAILURE em caso de falha de alocação
*/
operation_t *create_operation (int timestamp, int transaction_id, char op_type,char attribute);

/*!
    \brief Função que adiciona a operação no agendamento
    \param schedule Ponteiro de acesso para o agendamento 
    \param operation Ponteiro de acesso para uma operação
    \return EXIT_SUCCESS em caso de sucesso. EXIT_FAILURE em caso de falha de alocação
*/
void add_schedule_operation (schedule_t *schedule, operation_t *operation);

/*!
    \brief Função que realiza a leitura do agendamento enviado para o algoritimo
    \param schedule Ponteiro de acesso para a estrutura do agendamento
*/
int read_input_schedule (schedule_t **schedule);

/*!
    \brief Função que pega os ids das transações do agendamento
    \param schedule Ponteiro de acesso para o agendamento 
    \return EXIT_SUCCESS em caso de sucesso. EXIT_FAILURE em caso de falha de alocação
*/
int get_ids (schedule_t *schedule);

/*!
    \brief Função que limpa a memoria alocada para as estruturas
    \param schedule Ponteiro de acesso para a estrutura do agendamento
*/
void destroy_schedule (schedule_t *schedule);
#endif