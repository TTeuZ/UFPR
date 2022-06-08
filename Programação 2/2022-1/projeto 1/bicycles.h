#include "bicycle.h"

#ifndef BICYCLES_F
#define BICYCLES_F
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
* Função que limpa a memoria ocupada pelo estrutura de armazenamento das bicicletas
* Passa por cada bicicleta dentro do conjunto e chama sua função de limpeza
* Ao final, limpa a estrutura geral de armazenamento das bicicletas
*/
void clean_bicycles (bicycles_f *bicycles);

// função para adicionar uma bibicleta na lista
// função para verificar se uma bicicleta ja esta na lista
// função para atualizar/adicionar informação em uma bicicleta que está na lista
// função que gera um retorno da lista de atividades das bicicletas de acordo com um sort especificado
#endif