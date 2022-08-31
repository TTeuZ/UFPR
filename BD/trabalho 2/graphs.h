#ifndef _GRAPHS_H_
#define _GRAPHS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 

// Representação de um grafo por meio de uma matriz de adjacencias 

typedef struct graph {
    int vertices_qtd;
    int **adj_matrix;
} graph_t;

/*!
    \brief Função responsavel por alocar espaço em memoria para o grafo
    \param vertices_qtd quantidade de vertices que o grafo tera
    \return Ponteiro de acesso para o grafo em caso de sucesso. NULL em caso de falha
*/
graph_t *alloc_graph (int vertices_qtd);

/*!
    \brief Função que insere um arco no grafo
    \param graph Ponteiro para a estrutura do grafo
    \param origin_v vertice de origem do arco
    \param target_v vertice de chegada do arco
*/
void insert_edge (graph_t *graph, int origin_v, int target_v);

/*!
    \brief Função que verifica se o grafo tem um ciclo
    \param graph Ponteiro para a estrutura do grafo
    \return true para caso tenha, falso para caso não tenha
*/
int has_cycle (graph_t *graph);

/*!
    \brief Funcao responsavel por limpar a memoria armazenada para o grafo
    \param graph Ponteiro para umg grafo
*/
void destroy_graph (graph_t *graph);

#endif