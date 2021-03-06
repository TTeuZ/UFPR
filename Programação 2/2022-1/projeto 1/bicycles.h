#include "bicycle.h"

#ifndef BICYCLES
#define BICYCLES
typedef struct bicycles {
    bicycle_f **list;
    int qtd;
} bicycles_f;

/* 
*   Função que inicializa a estrutura de dados de armazenamento das bicicletas encontradas nos logs
*   Realiza a alocação inicial de espaço da estrutura e retorna o ponteiro de acesso
*/
bicycles_f *inicialize_bicycles ();

/*
*   Função que verifica se a bicicleta ja esta no conjunto
*   Retorna a posição da bicicleta no conjunto caso ja esteja adicionada 
*   Retorna -1 caso contrario
*/
int already_added (bicycles_f *bicycles, char *bicycle_name);

/*
*   Função que adiciona o log a uma bicicleta, ou cria uma nova bicicleta caso ainda não exista
*   Verifica se ja existe uma bicicleta para o log enviado, caso exista adiciona o log nela
*   caso não exista, cria uma nova bicicleta a adiciona o conjunto de bicicletas
*/
int verify_and_add_bicycle (bicycles_f *bicycles, bicycle_log_f *log);

/*
*   Função que adiciona uma nova bicicleta ao conjunto de bicicletas
*   inserção ordenada por nome
*/
int add_bicycle_to_array (bicycles_f *bicycles, bicycle_f *bicycle);

/*
*   Função que lista as bicicletas que foram armazenadas durante a leitura
*/
void list_bicycles (bicycles_f *bicycles);

/*
*   Função que printa todas as atividads armazenadas no conjunto
*   sort: Indica qual o sentido de ordenação do print
*/
void printf_all_activities (bicycles_f *bicycles, int sort);

/*
*   Função que limpa a memoria ocupada pelo estrutura de armazenamento das bicicletas
*   Passa por cada bicicleta dentro do conjunto e chama sua função de limpeza
*   Ao final, limpa a estrutura geral de armazenamento das bicicletas
*/
void clean_bicycles (bicycles_f *bicycles);
#endif