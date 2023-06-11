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
    if (!graph)
    {
        fprintf(stderr, "\nSomething went wrong with the graph allocation!\n\n");
        return 1;
    }

    if (agisdirected(graph))
    {
        topology = get_topology(graph);
        if (topology != NULL && topology->valid)
            print_topology(topology);
        else
            fprintf(stderr, "\nThe given graph has a cycle. Please, send a ADG (Acyclic Digraph) instead.\n\n");
    }
    else
        fprintf(stderr, "\nThe given graph is undirect. Please, send a ADG (Acyclic Digraph) instead.\n\n");

    if (topology != NULL)
        free_topology(topology);
    agclose(graph);
    return 0;
}