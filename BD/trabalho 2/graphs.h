#ifndef _GRAPHS_H_
#define _GRAPHS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

#endif