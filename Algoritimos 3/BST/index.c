#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

int main () {
    tree_t *tree;
    nodo_t *nodo;
    int count;
    tree = create_tree();

    printf("\n");
    printf("----------------------------------------------------------------\n");
    printf("Inserindo elementos na arvore\n");
    printf("\n");

    insert_in_leave (tree, tree->root, 10);
    insert_in_leave (tree, tree->root, 3);
    insert_in_leave (tree, tree->root, 15);
    insert_in_leave (tree, tree->root, 2);
    insert_in_leave (tree, tree->root, 33);
    insert_in_leave (tree, tree->root, 1);
    insert_in_leave (tree, tree->root, 34);
    insert_in_leave (tree, tree->root, 7);
    insert_in_leave (tree, tree->root, 90);
    insert_in_leave (tree, tree->root, 4);

    printf("quantidade de nodos da arvore: %d\n", tree->nodos_qtd);
    printf("Altura da arvore: %d\n", tree->height);

    printf("\n");
    printf("----------------------------------------------------------------\n");
    printf("Inserindo elementos na raiz arvore\n");
    printf("\n");

    insert_in_root (tree, tree->root, 70);
    printf("Raiz da arvore: %d\n", tree->root->value);
    insert_in_root (tree, tree->root, 12);
    printf("Raiz da arvore: %d\n", tree->root->value);
    insert_in_root (tree, tree->root, 92);
    printf("Raiz da arvore: %d\n", tree->root->value);

    printf("\n");
    printf("----------------------------------------------------------------\n");
    printf("Imprimindo arvore\n");
    printf("\n");

    in_order (tree->root);
    printf("\n");
    printf("Raiz da arvore: %d\n", tree->root->value);

    printf("\n");
    printf("----------------------------------------------------------------\n");
    printf("Rotacionando arvore para a direita, pela raiz\n");
    printf("\n");

    right_rotate_tree (tree, tree->root);

    printf("\n");
    printf("----------------------------------------------------------------\n");
    printf("Imprimindo arvore\n");
    printf("\n");

    in_order (tree->root);
    printf("\n");
    printf("Raiz da arvore: %d\n", tree->root->value);

    printf("\n");
    printf("----------------------------------------------------------------\n");
    printf("Rotacionando arvore para a esquerda, pela raiz\n");
    printf("\n");

    left_rotate_tree (tree, tree->root);

    printf("\n");
    printf("----------------------------------------------------------------\n");
    printf("Imprimindo arvore\n");
    printf("\n");

    in_order (tree->root);
    printf("\n");
    printf("Raiz da arvore: %d\n", tree->root->value);

    /*printf("\n");
    printf("----------------------------------------------------------------\n");
    printf("Buscando o valor minimo a partir da raiz\n");
    printf("\n");

    nodo = tree_minimum (tree->root);
    printf("valor: %d\n", nodo->value);

    printf("\n");
    printf("----------------------------------------------------------------\n");
    printf("Buscando o valor minimo a partir da direita da raizz\n");
    printf("\n");

    nodo = tree_minimum (tree->root->right);
    printf("valor: %d\n", nodo->value);

    printf("\n");
    printf("----------------------------------------------------------------\n");
    printf("Buscando o valor minimo a partir da esquerda da raiz\n");
    printf("\n");

    nodo = tree_minimum (tree->root->left);
    printf("valor: %d\n", nodo->value); */

    printf("\n");
    printf("----------------------------------------------------------------\n");
    printf("Buscando valores da arvore\n");
    printf("\n");

    for (count = 0; count <= 15; count++) {
        if ((nodo = search_tree (tree->root, count)))
            printf("Valor encontrado: %d\n", nodo->value);
        else
            printf("Valor %d não está na árvore\n", count);
    }

    printf("\n");
    printf("----------------------------------------------------------------\n");
    printf("removendo todos os elementos a partir da raiz\n");
    printf("\n");

    count = tree->nodos_qtd;
    for (count = tree->nodos_qtd; count > 0; count--) {
        transplant_nodo_delete (tree, tree->root);
        in_order (tree->root);
        printf("\n\n");
        if (tree->root != NULL)
            printf("Raiz da arvore: %d\n", tree->root->value);
        printf("altura da arvore: %d\n", tree->height);
        printf("numero de nodos da arvore: %d\n", tree->nodos_qtd);
        printf("\n");
    } 

    free (tree);

    return 0;
}