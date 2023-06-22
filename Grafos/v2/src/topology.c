#include "topology.h"

/* ============================== Internal Functions ============================== */

/*!
    \brief Recursive function to the DFS search to find the topology
    \param graph Pointer to the graph structure.
    \param node Node 'root' of the respective call
    \param topology Pointer to the topology structure
    \param has_cycle int value that indicates whether it has a cycle or not
*/
void topology_dfs(Agraph_t *graph, Agnode_t *node, topology_t *topology, int *has_cycle)
{
    Agnode_t *neigh_node;
    Agedge_t *edge;
    dfs_node_t *info;

    info = (dfs_node_t *)aggetrec(node, "dfs_node_t", FALSE);
    info->state = 1;

    for (edge = agfstout(graph, node); edge && !(*has_cycle); edge = agnxtout(graph, edge))
    {
        neigh_node = aghead(edge);
        info = (dfs_node_t *)aggetrec(neigh_node, "dfs_node_t", FALSE);

        if (info->state == 0)
            topology_dfs(graph, aghead(edge), topology, has_cycle);
        else if (info->state == 1)
            *has_cycle = TRUE;
    }

    info = (dfs_node_t *)aggetrec(node, "dfs_node_t", FALSE);
    info->state = 2;
    add_to_topology(topology, node);
}

/* ============================== Internal Functions ============================== */

topology_t *alloc_topology(Agraph_t *graph)
{
    int nodes_qty;
    topology_t *temp;

    nodes_qty = agnnodes(graph);
    temp = malloc(sizeof(topology_t));
    if (!temp)
        return NULL;

    temp->list = malloc(nodes_qty * sizeof(Agnode_t *));
    if (!temp->list)
    {
        free(temp);
        return NULL;
    }

    temp->size = nodes_qty;
    temp->count = 0;
    return temp;
}

void free_topology(topology_t *topology)
{
    free(topology->list);
    free(topology);
}

void add_to_topology(topology_t *topology, Agnode_t *node)
{
    topology->list[topology->count] = node;
    topology->count++;
}

int get_topology(Agraph_t *graph, topology_t *topology)
{
    int has_cycle;
    Agnode_t *node;
    dfs_node_t *info;

    has_cycle = FALSE;
    for (node = agfstnode(graph); node && !has_cycle; node = agnxtnode(graph, node))
    {
        info = (dfs_node_t *)aggetrec(node, "dfs_node_t", FALSE);
        if (info->state == 0)
            topology_dfs(graph, node, topology, &has_cycle);
    }

    return !has_cycle;
}

void print_topology(topology_t *topology)
{
    int count;

    for (count = topology->size - 1; count > 0; count--)
        printf("%s ", agnameof(topology->list[count]));
    printf("%s\n", agnameof(topology->list[count]));
}
