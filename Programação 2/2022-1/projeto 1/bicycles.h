#include "bicycle.h"

#ifndef BICYCLES
#define BICYCLES
typedef struct bicycles {
    bicycle_f **bicycles;
    int qtd;
} bicycles_f;

/* 
* Função que inicializa a estrutura de dados de armazenamento das bicicletas encontradas nos logs
* Realiza a alocação inicial de espaço da propia estrutura e retorna o ponteiro de acesso
*/
bicycles_f *inicialize_bicycles ();

/*
* Função que adiciona o log a uma bicicleta, ou cria uma nova bicicleta caso ainda não exista
* Verifica se ja existe uma bicicleta para o log enviado, caso exista adiciona o log nela
* caso não exista, cria uma nova bicicleta a adiciona o conjunto de bicicletas
*/
void add_bicycle_log (bicycles_f *bicycles, bicycle_log_f *log);

/*
* Função que limpa a memoria ocupada pelo estrutura de armazenamento das bicicletas
* Passa por cada bicicleta dentro do conjunto e chama sua função de limpeza
* Ao final, limpa a estrutura geral de armazenamento das bicicletas
*/
void clean_bicycles (bicycles_f *bicycles);

// função para verificar se uma bicicleta ja esta na lista
// função para atualizar/adicionar informação em uma bicicleta que está na lista
// função que gera um retorno da lista de atividades das bicicletas de acordo com um sort especificado
#endif