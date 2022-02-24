#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

tree_t *create_tree () {
    tree_t *tree;
    if ((tree = malloc (sizeof (tree_t)))) {
        tree->root = NULL;
        tree->nodos_qtd = 0;
        tree->height = 0;
        return tree;
    } else return NULL;
}

nodo_t *create_nodo (int value) {
    nodo_t *nodo;
    if ((nodo = malloc (sizeof (nodo_t)))) {
        nodo->value = value;
        nodo->left = NULL;
        nodo->right = NULL;
        nodo->father = NULL;
        return nodo;
    } else return NULL;
}

nodo_t *insert_in_leave (tree_t *tree, nodo_t *nodo, int value) {
    nodo_t *inside_nodo;
    if (nodo == NULL) { 
        inside_nodo = create_nodo(value);
        if (tree->root == NULL)
            tree->root = inside_nodo;
        tree->nodos_qtd++;
        tree->height = tree_height(tree->root);
        return inside_nodo;
    }
    if (value < nodo->value) {
        nodo->left = insert_in_leave (tree, nodo->left, value);
        nodo->left->father = nodo;
    } else {
        nodo->right = insert_in_leave (tree, nodo->right, value);
        nodo->right->father = nodo;
    }
    return nodo;
}

void left_rotate_tree (tree_t *tree, nodo_t *nodo) {
    nodo_t *inside_nodo;

    inside_nodo = nodo->right;
    nodo->right = inside_nodo->left;
    inside_nodo->father = nodo->father;

    /* Se o nodo rotacionado virar a nova raiz, altera na struct da arvore */
    if (inside_nodo->father == NULL) tree->root = inside_nodo;
    nodo->father = inside_nodo;

    if (inside_nodo->left != NULL) inside_nodo->left->father = nodo;
    inside_nodo->left = nodo;
}

void right_rotate_tree (tree_t *tree, nodo_t *nodo) {
    nodo_t *inside_nodo;

    inside_nodo = nodo->left;
    nodo->left = inside_nodo->right;
    inside_nodo->father = nodo->father;

    /* Se o nodo rotacionado virar a nova raiz, altera na struct da arvore */
    if (inside_nodo->father == NULL) tree->root = inside_nodo;
    nodo->father = inside_nodo;

    if (inside_nodo->right != NULL) inside_nodo->right->father = nodo;
    inside_nodo->right = nodo;
}

int tree_height (nodo_t *nodo) {
    int height_left, height_right;
    if (nodo == NULL) return 0;

    height_left = tree_height (nodo->left);
    height_right = tree_height (nodo->right);

    if (height_left > height_right) return height_left+1;
    else return height_right+1;
}

nodo_t *tree_minimum (nodo_t *nodo) {
    if (nodo->left == NULL) return nodo;
    else return tree_minimum(nodo->left);
}

void nodo_transplant (tree_t *tree, nodo_t *removed, nodo_t *transplanted) {
    if (removed->father == NULL) 
        tree->root = transplanted;
    else if (removed == removed->father->left)
        removed->father->left = transplanted;
    else 
        removed->father->right = transplanted;
    if (transplanted != NULL)
        transplanted->father = removed->father;
}

void transplant_nodo_delete (tree_t *tree, nodo_t *nodo) {
    nodo_t *inside_nodo;
    if (nodo->left == NULL) {
        nodo_transplant (tree, nodo, nodo->right);
        free (nodo);
    } else if (nodo->right == NULL) {
        nodo_transplant (tree, nodo, nodo->left);
        free (nodo);
    } else {
        inside_nodo = tree_minimum (nodo->right);
        if (inside_nodo->father != nodo) {
            nodo_transplant (tree, inside_nodo, inside_nodo->right);
            inside_nodo->right = nodo->right;
            inside_nodo->right->father = inside_nodo;
        }
        nodo_transplant (tree, nodo, inside_nodo);
        inside_nodo->left = nodo->left;
        inside_nodo->left->father = inside_nodo;
        free (nodo);
    }
    tree->nodos_qtd--;
    tree->height = tree_height (tree->root);
}

void in_order (nodo_t *nodo) {
    if (nodo != NULL) {
        in_order (nodo->left);
        printf (" %d ", nodo->value);
        in_order (nodo->right);
    } 
}

nodo_t *search_tree (nodo_t *nodo, int value) {
    if (nodo == NULL) return NULL;
    if (nodo->value == value) return nodo;
    if (value < nodo->value) 
        return search_tree (nodo->left, value);
    else return search_tree (nodo->right, value);
}