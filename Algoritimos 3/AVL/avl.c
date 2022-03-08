#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

/*-------------------------------Funções internas----------------------------------*/
/*
* Função que retorna a altura do nodo indicado, e caso seja NULL, retorna 0.
*/
int tree_height (nodo_t *nodo) {
    int height_left, height_right;
    if (nodo == NULL) return -1;

    height_left = tree_height (nodo->left);
    height_right = tree_height (nodo->right);

    if (height_left > height_right) return height_left + 1;
    else return height_right + 1;
}

/*
* Função que retorna a diferença da altura da subarvore da esquerda
* com a da direita.
*/
int get_balance (nodo_t *nodo) {
    if (nodo == NULL) return 0;
    else return tree_height (nodo->left) - tree_height (nodo->right);
}

/*-------------------------------Funções internas----------------------------------*/


tree_t *create_tree () {
    tree_t *tree;
    if ((tree = malloc (sizeof (tree_t)))) {
        tree->root = NULL;
        tree->nodos_qtd = 0;
        return tree;
    } else return NULL;
}

nodo_t *create_nodo (int value) {
    nodo_t *nodo;
    if ((nodo = malloc (sizeof (nodo_t)))) {
        nodo->value = value;
        nodo->height = 0;
        nodo->left = NULL;
        nodo->right = NULL;
        nodo->father = NULL;
        return nodo;
    } else return NULL;
}

void in_order (tree_t *tree, nodo_t *nodo, int level) {
    if (nodo != NULL) {
        in_order (tree, nodo->left, ++level);
        printf ("%d,%d\n", nodo->value, level - 1);
        in_order (tree, nodo->right, level);
    } 
}

nodo_t *search_tree (nodo_t *nodo, int value) {
    if (nodo == NULL) return NULL;
    if (nodo->value == value) return nodo;
    if (value < nodo->value) 
        return search_tree (nodo->left, value);
    else return search_tree (nodo->right, value);
}

nodo_t *left_rotate_tree (tree_t *tree, nodo_t *nodo, int d_value) {
    nodo_t *inside_nodo;
    int height;

    inside_nodo = nodo->right;
    nodo->right = inside_nodo->left;
    inside_nodo->father = nodo->father;
    nodo->father = inside_nodo;
    if (inside_nodo->left != NULL) inside_nodo->left->father = nodo;

    /* Se o nodo rotacionado virar a nova raiz, altera na struct da arvore. */
    if (inside_nodo->father == NULL) tree->root = inside_nodo;
    inside_nodo->left = nodo;

    height = inside_nodo->height;
    inside_nodo->height = nodo->height - d_value;
    nodo->height = height - d_value;

    return inside_nodo;
}

nodo_t *right_rotate_tree (tree_t *tree, nodo_t *nodo, int d_value) {
    nodo_t *inside_nodo;
    int height;

    inside_nodo = nodo->left;
    nodo->left = inside_nodo->right;
    inside_nodo->father = nodo->father;
    nodo->father = inside_nodo;
    if (inside_nodo->right != NULL) inside_nodo->right->father = nodo;

    /* Se o nodo rotacionado virar a nova raiz, altera na struct da arvore */
    if (inside_nodo->father == NULL) tree->root = inside_nodo;
    inside_nodo->right = nodo;

    height = inside_nodo->height;
    inside_nodo->height = nodo->height - d_value;
    nodo->height = height - d_value;

    return inside_nodo;
}

nodo_t *insert_in_leave (tree_t *tree, nodo_t *nodo, int value) {
    nodo_t *inside_nodo;
    int balance;

    if (nodo == NULL) { 
        inside_nodo = create_nodo (value);

        if (tree->root == NULL)
            tree->root = inside_nodo;
        tree->nodos_qtd++;

        return inside_nodo;
    }
    if (value < nodo->value) {
        nodo->left = insert_in_leave (tree, nodo->left, value);
        nodo->left->father = nodo;
    } else if (value > nodo->value) {
        nodo->right = insert_in_leave (tree, nodo->right, value);
        nodo->right->father = nodo;
    } else return nodo;
    
    nodo->height = tree_height (nodo);
    balance = get_balance (nodo);

    /* zig-zig para a caso da esquerda */
    if (balance == 2 && value < nodo->left->value) 
        return right_rotate_tree (tree, nodo, 1);
    /* zig-zig para a caso da direita */
    if (balance == -2 && value > nodo->right->value) 
        return left_rotate_tree (tree, nodo, 1);
    /* zig-zag para a caso da esquerda */
    if (balance == 2 && value > nodo->left->value) {
        nodo->left = left_rotate_tree (tree, nodo->left, 0);
        return right_rotate_tree (tree, nodo, 1);
    }
    /* zig-zag para a caso da direita */
    if (balance == -2 && value < nodo->right->value) {
        nodo->right = right_rotate_tree (tree, nodo->right, 0);
        return left_rotate_tree (tree, nodo, 1);
    }

    return nodo;
}

nodo_t *predecessor(nodo_t *nodo) {
    if (nodo->right == NULL) return nodo;
    else return predecessor (nodo->right);
}

void nodo_transplant (tree_t *tree, nodo_t *removed, nodo_t *transplanted) {
    if (removed->father == NULL) 
        tree->root = transplanted;
    else if (removed->father->left == NULL && removed->father->right == NULL)
        removed->father->height--;
    else if (removed == removed->father->left)
        removed->father->left = transplanted;
    else 
        removed->father->right = transplanted;
    if (transplanted != NULL) {
        transplanted->height = removed->height;
        transplanted->father = removed->father;
    }
}

void transplant_nodo_delete (tree_t *tree, nodo_t *nodo) {
    nodo_t *inside_nodo, *w_nodo;
    int balance;

    if (nodo->left == NULL) {
        w_nodo = nodo->father;
        nodo_transplant (tree, nodo, nodo->right);
    } else if (nodo->right == NULL) {
        w_nodo = nodo->father;

        nodo_transplant (tree, nodo, nodo->left);
    } else {
        inside_nodo = predecessor (nodo->left);
        if (nodo->father != NULL)
            w_nodo = nodo->father;
        else w_nodo = inside_nodo->father;

        if (inside_nodo->father != nodo) {
            nodo_transplant (tree, inside_nodo, inside_nodo->left);
            inside_nodo->left = nodo->left;
            inside_nodo->left->father = inside_nodo;
        }
        nodo_transplant (tree, nodo, inside_nodo);
        inside_nodo->right = nodo->right;
        inside_nodo->right->father = inside_nodo;
    }
    
    while (w_nodo != NULL) {
        balance = get_balance (w_nodo);
        if (balance == 2) {
            right_rotate_tree (tree, w_nodo, 1);
        } else if (balance == -2) {
            left_rotate_tree (tree, w_nodo, 1);
        }
        w_nodo = w_nodo->father;
    }

    free (nodo);
    tree->nodos_qtd--;
}