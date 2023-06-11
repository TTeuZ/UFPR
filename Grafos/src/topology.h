#ifndef __TOPOLOGY__
#define __TOPOLOGY__

#include <graphviz/cgraph.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct dfs_node
{
    Agrec_t header;
    int pre;
    int pos;
    int state;
} dfs_node_t;

typedef struct topology
{
    int size;
    // Agnode_t array?
} topology_t;

/*!
    \brief Get the topology for the given graph.
    \param graph Pointer to the graph structure.
    \return NULL if the graph has cycle. A pointer to the topology structure if it hasn't.
*/
topology_t *get_topology(Agraph_t *graph);

/*!
    \brief Print out the topology for the given graph
    \param topology Pointer to the topology structure.
*/
void print_topology(topology_t *topology);

#endif