#ifndef __UTILS__
#define __UTILS__

#include <graphviz/cgraph.h>
#include <stdlib.h>
#include <stdio.h>

#include "topology.h"

/*!
    \brief Verify if the given graph is acyclic
    \param graph Pointer to the graph structure.
    \return TRUE if it is acyclic, FALSE otherwise.
*/
int is_acyclic(Agraph_t *graph);

#endif