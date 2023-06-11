#include "utils.h"

/* ============================== Internal Functions ============================== */

/*!
    \brief Recursive function to the DFS search
    \param graph Pointer to the graph structure.
    \param node Node 'root' of the respective call
    \param index same as the 't' in the DFS
*/
void acyclic_dfs(Agraph_t *graph, Agnode_t *node, int *index)
{
    Agnode_t *neigh_node;
    Agedge_t *edge;
    dfs_node_t *info;

    info = (dfs_node_t *)aggetrec(node, "dfs_node_t", FALSE);
    info->state = 1;
    info->pre = ++(*index);

    for (edge = agfstout(graph, node); edge; edge = agnxtout(graph, edge))
    {
        neigh_node = aghead(edge);
        info = (dfs_node_t *)aggetrec(neigh_node, "dfs_node_t", FALSE);

        if (info->state == 0)
            acyclic_dfs(graph, aghead(edge), index);
    }

    info = (dfs_node_t *)aggetrec(node, "dfs_node_t", FALSE);
    info->state = 2;
    info->pos = ++(*index);
}

/* ============================== Internal Functions ============================== */

int is_acyclic(Agraph_t *graph)
{
    int index;
    Agnode_t *node;
    Agedge_t *edge;
    dfs_node_t *info, *info_tail, *info_head;

    index = 0;
    for (node = agfstnode(graph); node; node = agnxtnode(graph, node))
    {
        info = (dfs_node_t *)aggetrec(node, "dfs_node_t", FALSE);
        if (info->state == 0)
            acyclic_dfs(graph, node, &index);
    }

    for (node = agfstnode(graph); node; node = agnxtnode(graph, node))
    {
        for (edge = agfstout(graph, node); edge; edge = agnxtout(graph, edge))
        {
            info_tail = (dfs_node_t *)aggetrec(agtail(edge), "dfs_node_t", FALSE);
            info_head = (dfs_node_t *)aggetrec(aghead(edge), "dfs_node_t", FALSE);

            if (info_head->pre < info_tail->pre && info_tail->pos < info_head->pos)
                return FALSE;
        }
        info = (dfs_node_t *)aggetrec(node, "dfs_node_t", FALSE);
        info->state = 0;
    }

    return TRUE;
}