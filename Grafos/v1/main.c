#include <stdio.h>
#include <stdlib.h>
#include <graphviz/cgraph.h>

#include "src/topology.h"
#include "src/utils.h"

int main()
{
    Agraph_t *graph;
    topology_t *topology;

    graph = agread(stdin, NULL);
    topology = alloc_topology(graph);
    if (!graph || !topology)
    {
        fprintf(stderr, "\nSomething went wrong with the graph allocation!\n\n");
        return 1;
    }

    // Binding with the dfs_node_t for internal attributes
    // The aginit already initalize the values of dfs_node_t with 0.
    aginit(graph, 1, "dfs_node_t", sizeof(dfs_node_t), FALSE);

    if (agisdirected(graph) && is_acyclic(graph))
    {
        get_topology(graph, topology);
        print_topology(topology);
    }
    else
        fprintf(stderr, "\nThe given graph is not a DAG. Please, send a DAG (Direct Acyclic Graph) instead.\n\n");

    free_topology(topology);
    agclose(graph);
    return 0;
}