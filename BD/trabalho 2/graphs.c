#include "graphs.h"

graph_t *alloc_graph (int vertices_qtd) {
    graph_t *graph;
    int count;

    if (! (graph = malloc (sizeof (graph_t))))
        return NULL;
    
    graph->vertices_qtd = vertices_qtd;
    
    // Matriz com um vetor de vertices_qtd ponteiros para o mesmo vertor de vertices_qtd^2 de tamanho

    if (! (graph->adj_matrix = (int **) malloc (sizeof (int *) * vertices_qtd)))
        return NULL;
    if (! (graph->adj_matrix[0] = (int *) malloc (sizeof (int) * vertices_qtd * vertices_qtd)))
        return NULL;
    
    for (count = 1; count < vertices_qtd; ++count)
        graph->adj_matrix[count] = graph->adj_matrix[count - 1] + vertices_qtd;
    
    // seta a matriz para 0
    memset (graph->adj_matrix[0], 0, sizeof (int) * vertices_qtd * vertices_qtd);
    return graph;
}

void insert_edge (graph_t *graph, int origin_v, int target_v) {
    if (graph->adj_matrix[origin_v][target_v] == 0)
        graph->adj_matrix[origin_v][target_v] = 1;
}

void destroy_graph (graph_t *graph) {
    free (graph->adj_matrix[0]);
    free (graph->adj_matrix);
    free (graph);
}