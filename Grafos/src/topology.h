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
    int count;
    Agnode_t **list;
} topology_t;

/*!
    \brief Alocate memory for the topology structure
    \param graph Pointer to the graph structure.
    \return NULL if something went wrong with the allocation. A pointer to the strcuture if success.
*/
topology_t *alloc_topology(Agraph_t *graph);

/*!
    \brief Free the memory allocated for the topology structure
    \param topology Pointer to the topology structure.
*/
void free_topology(topology_t *topology);

/*!
    \brief Add the node to topology sort
    \param topology Pointer to the topology structure.
    \param node Node 'root' of the respective call
*/
void add_to_topology(topology_t *topology, Agnode_t *node);

/*!
    \brief Get the topology for the given graph.
    \param graph Pointer to the graph structure.
    \param topology Pointer to the topology structure.
    \return NULL if the graph has cycle. A pointer to the topology structure if it hasn't.
*/
void get_topology(Agraph_t *graph, topology_t *topology);

/*!
    \brief Print out the topology for the given graph
    \param topology Pointer to the topology structure.
*/
void print_topology(topology_t *topology);

#endif