#include "topology.h"

topology_t *topology_dfs(Agraph_t *graph, Agnode_t *node)
{
    Agnode_t *neigh_node;
    Agedge_t *edge;
    Agrec_t *record;
    dfs_node_t *teste;
    for (node; node; node = agnxtnode(graph, node))
        for (edge = agfstout(graph, node); edge; edge = agnxtout(graph, edge))
        {
            neigh_node = aghead(edge);
            // record = aggetrec(neigh_node, "dfs_node_t", FALSE);
            // printf("record: %s\n", record->name);
            teste = (dfs_node_t *)(neigh_node->base.data);
            printf("teste: %d\n", teste->state);
            topology_dfs(graph, aghead(edge));
        }

    return NULL;
}

topology_t *get_topology(Agraph_t *graph)
{
    // seta os estados
    // faz a primeira chamada

    Agnode_t *node;
    dfs_node_t *teste;
    node = agfstnode(graph);
    teste = (dfs_node_t *)(node->base.data);
    teste->state = 3;

    return topology_dfs(graph, node);
}

void print_topology(topology_t *topology)
{
}

// printf("Tail: %s --> Head: %s\n", agnameof(agtail(edge)), agnameof(aghead(edge)));