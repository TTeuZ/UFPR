#include "topology.h"

/* ============================== Internal Functions ============================== */

/*!
    \brief Recursive function to the DFS search
    \param graph Pointer to the graph structure.
    \param node Node 'root' of the respective call
    \param topology Pointer to the topology structure
    \param index same as the 't' in the DFS
*/
void topology_dfs(Agraph_t *graph, Agnode_t *node, topology_t *topology, int *index)
{
    Agnode_t *neigh_node;
    Agedge_t *edge;
    dfs_node_t *info, *info_tail, *info_head;

    info = (dfs_node_t *)aggetrec(node, "dfs_node_t", FALSE);
    info->state = 1;
    info->pre = ++(*index);

    for (edge = agfstout(graph, node); edge && topology->valid; edge = agnxtout(graph, edge))
    {
        neigh_node = aghead(edge);
        info = (dfs_node_t *)aggetrec(neigh_node, "dfs_node_t", FALSE);

        if (info->state == 0)
            topology_dfs(graph, aghead(edge), topology, index);
        else
        {
            info_tail = (dfs_node_t *)aggetrec(agtail(edge), "dfs_node_t", FALSE);
            info_head = (dfs_node_t *)aggetrec(aghead(edge), "dfs_node_t", FALSE);
            printf("%d < %d\n", info_head->pre, info_tail->pre);
            if (info_head->pre < info_tail->pre)
                topology->valid = FALSE;
        }
    }

    info = (dfs_node_t *)aggetrec(node, "dfs_node_t", FALSE);
    info->state = 2;
    info->pos = ++(*index);
    if (topology->valid)
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
    temp->valid = TRUE;
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

topology_t *get_topology(Agraph_t *graph)
{
    int index;
    Agnode_t *node;
    dfs_node_t *info;
    topology_t *topology;

    index = 0;
    topology = alloc_topology(graph);
    if (!topology)
        return NULL;

    // Binding with the dfs_node_t for internal attributes
    // The aginit already initalize the values of dfs_node_t with 0.
    aginit(graph, 1, "dfs_node_t", sizeof(dfs_node_t), FALSE);
    for (node = agfstnode(graph); node && topology->valid; node = agnxtnode(graph, node))
    {
        info = (dfs_node_t *)aggetrec(node, "dfs_node_t", FALSE);
        if (info->state == 0)
            topology_dfs(graph, node, topology, &index);
    }

    return topology;
}

void print_topology(topology_t *topology)
{
    int count;

    for (count = topology->size - 1; count > 0; count--)
        printf("%s ", agnameof(topology->list[count]));
    printf("%s\n", agnameof(topology->list[count]));
}
