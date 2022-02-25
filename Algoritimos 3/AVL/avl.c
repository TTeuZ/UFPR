#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

/*-------------------------------Funções internas----------------------------------*/
/*
* Função que retorna a altura do nodo indicado, e caso seja null, retorna 0;
*/
int tree_height (nodo_t *nodo) {
    int height_left, height_right;
    if (nodo == NULL) return 0;

    height_left = tree_height (nodo->left);
    height_right = tree_height (nodo->right);

    if (height_left > height_right) return height_left + 1;
    else return height_right + 1;
}

/*
* Função que seta as alturas de todos os nodos abaixo do nodo inserido, apartir de um valor base
* e atualiza a altura da arvore
*/
void set_new_heights (tree_t *tree, nodo_t *nodo, int height) {
    if (nodo == NULL) return;
    nodo->height = height;
    set_new_heights (tree, nodo->left, ++height);
    set_new_heights (tree, nodo->right, height);
    if (tree->height > height)
        tree->height = height;
}

/*
* Função que retorna a altura do nodo em questão, caso o nodo enviado seja null, retorna 0
*/
/*int nodo_height (nodo_t *nodo) {
    if (nodo == NULL) return 0;
    return nodo->height;
} */

/*
* Função que retorna a diferença da altura da folha mais distante da subarvore da esquerda
* com a da direita
*/
int get_balance (nodo_t *nodo) {
    if (nodo == NULL) return 0;
    return tree_height (nodo->left) - tree_height (nodo->right);
}
/*-------------------------------Funções internas----------------------------------*/


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
        nodo->height = 0;
        nodo->left = NULL;
        nodo->right = NULL;
        nodo->father = NULL;
        return nodo;
    } else return NULL;
}

void in_order (nodo_t *nodo) {
    if (nodo != NULL) {
        in_order (nodo->left);
        printf ("%d,%d\n", nodo->value, nodo->height);
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

nodo_t *left_rotate_tree (tree_t *tree, nodo_t *nodo) {
    nodo_t *inside_nodo;
    int height;

    inside_nodo = nodo->right;
    nodo->right = inside_nodo->left;
    if (inside_nodo->left != NULL) inside_nodo->left->father = nodo;

    inside_nodo->father = nodo->father;

    /* Se o nodo rotacionado virar a nova raiz, altera na struct da arvore */
    if (nodo->father == NULL) tree->root = inside_nodo;
    else if (nodo->father->left == nodo) nodo->father->left = inside_nodo;
    else nodo->father->right = inside_nodo;

    inside_nodo->left = nodo;

    height = inside_nodo->height;
    inside_nodo->height = nodo->height;
    nodo->height = height;

    set_new_heights (tree, inside_nodo, inside_nodo->height);

    return inside_nodo;
}

nodo_t *right_rotate_tree (tree_t *tree, nodo_t *nodo) {
    nodo_t *inside_nodo;
    int height;

    inside_nodo = nodo->left;
    nodo->left = inside_nodo->right;
    if (inside_nodo->right != NULL) inside_nodo->right->father = nodo;

    inside_nodo->father = nodo->father;

    /* Se o nodo rotacionado virar a nova raiz, altera na struct da arvore */
    if (nodo->father == NULL) tree->root = inside_nodo;
    else if (nodo->father->right == nodo) nodo->father->right = inside_nodo;
    else nodo->father->left = inside_nodo;

    inside_nodo->right = nodo;

    height = inside_nodo->height;
    inside_nodo->height = nodo->height;
    nodo->height = height;

    set_new_heights (tree, inside_nodo, inside_nodo->height);

    return inside_nodo;
}

nodo_t *insert_in_leave (tree_t *tree, nodo_t *nodo, int height, int value) {
    nodo_t *inside_nodo;
    int balance;

    if (nodo == NULL) { 
        inside_nodo = create_nodo(value);
        inside_nodo->height = height;

        tree->height = height;
        if (tree->root == NULL)
            tree->root = inside_nodo;
        tree->nodos_qtd++;

        return inside_nodo;
    }
    if (value < nodo->value) {
        nodo->left = insert_in_leave (tree, nodo->left, ++height, value);
        nodo->left->father = nodo;
    } else if (value > nodo->value) {
        nodo->right = insert_in_leave (tree, nodo->right, ++height, value);
        nodo->right->father = nodo;
    } else return nodo;

    balance = get_balance (nodo);

    /* zig-zig para a caso da esquerda */
    if (balance > 1 && value < nodo->left->value) 
        return right_rotate_tree (tree, nodo);
    /* zig-zig para a caso da direita */
    if (balance < -1 && value > nodo->right->value) 
        return left_rotate_tree (tree, nodo);
    /* zig-zag para a caso da esquerda */
    if (balance > 1 && value > nodo->left->value) {
        nodo->left = left_rotate_tree (tree, nodo->left);
        return right_rotate_tree (tree, nodo);
    }
    /* zig-zag para a caso da direita*/
    if (balance < -1 && value < nodo->right->value) {
        nodo->right = right_rotate_tree (tree, nodo->right);
        return left_rotate_tree (tree, nodo);
    }

    return nodo;
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
        printf("aqui mermo: %d\n", inside_nodo->value);
         if (inside_nodo->father != nodo) {
            nodo_transplant (tree, inside_nodo, inside_nodo->right);
            inside_nodo->right = nodo->right;
            inside_nodo->right->father = inside_nodo;
        }
        nodo_transplant (tree, nodo, inside_nodo);
        inside_nodo->left = nodo->left;
        inside_nodo->left->father = inside_nodo;
        free (nodo); */
    }
    tree->nodos_qtd--;
}