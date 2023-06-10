#include <stdio.h>
#include <stdlib.h>
#include <graphviz/cgraph.h>

#include "src/topology.h"

int main()
{
    Agraph_t *graph;
    topology_t *topology;

    topology = NULL;
    graph = agread(stdin, NULL);
    if (agisdirected(graph))
    {
        topology = get_topology(graph);
        if (topology != NULL)
            print_topology(topology);
        else
            fprintf(stderr, "\nThe given graph has a cycle. Please, send a ADG (Acyclic Digraph) instead.\n\n");
    }
    else
        fprintf(stderr, "\nThe given graph is undirect. Please, send a ADG (Acyclic Digraph) instead.\n\n");

    if (topology != NULL)
        free(topology);
    agclose(graph);
    return 0;
}