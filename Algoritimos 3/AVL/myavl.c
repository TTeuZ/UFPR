#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int main () {
    tree_t *tree;
    nodo_t *nodo;
    char action;
    int value;

    /* inicializa a estrutura da árvore AVL*/
    tree = create_tree();

    /* busca a primeira ação e o primeiro valor do stdin */
    fscanf (stdin, "%c %d", &action, &value);
    getc (stdin);

    /* começa a executar até o arquivo acabar */
    while (! feof (stdin)) {
        /* seleciona e executa a ação indicada */
        if (action == 'i') 
            insert_in_leave (tree, tree->root, 0, value);
         else if ((nodo = search_tree (tree->root, value)))
            transplant_nodo_delete (tree, nodo);

        /* busca a proxima ação e valor do stdin */
        fscanf (stdin, "%c %d", &action, &value);
        getc (stdin);
    }

    /* faz a impressão da arvore resultante */
    in_order (tree->root);

    /* limpa as estruturas na finalização do programa */
    /* while (tree->nodos_qtd > 0) {
        transplant_nodo_delete (tree, tree->root);
    }
    free (tree); */

    return 0;
}