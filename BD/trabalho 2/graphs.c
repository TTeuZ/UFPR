#include "graphs.h"
//------------------------------------- Funções interanas -------------------------------------
/*!
    \brief Função auxiliar de chegagem de ciclo
    \param grafh Ponteiro para o grafo
    \param accessed_vertices Vetor com os vertices que foram acessados
    \param actual vertice atual
    \return true para caso tenha encontrado ciclo. Falso para caso não
*/
int check_cycle (graph_t *graph, int *accessed_vertices, int actual) {
    int flag = false;
    int count;

    if (accessed_vertices[actual]) return true;

    accessed_vertices[actual] = true;
    for (count = 0; count < graph->vertices_qtd; count++) {
        if (graph->adj_matrix[actual][count] == 1) {
            flag = check_cycle (graph, accessed_vertices, count);
            if (flag) {
                accessed_vertices[actual] = false;
                return true;
            }
        }
    }
    accessed_vertices[actual] = false;
    return false;
}

//------------------------------------- Funções interanas -------------------------------------


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

int has_cycle (graph_t *graph) {
    int *accessed_vertices;
    int i, j, flag;

    if (! (accessed_vertices = malloc (sizeof (int) * graph->vertices_qtd)))
        return -1;
    memset (accessed_vertices, 0, sizeof (int) * graph->vertices_qtd);

    for (i = 0; i < graph->vertices_qtd; i++) {
        accessed_vertices[i] = true;
        for (j = 0; j < graph->vertices_qtd; j++) {
            if (graph->adj_matrix[i][j] == 1) {
                flag = check_cycle (graph, accessed_vertices, j);
                if (flag) {
                    free (accessed_vertices);
                    return true;
                }
            }
        }
        accessed_vertices[i] = false;
    }

    free (accessed_vertices);
    return false;
}

void destroy_graph (graph_t *graph) {
    free (graph->adj_matrix[0]);
    free (graph->adj_matrix);
    free (graph);
}