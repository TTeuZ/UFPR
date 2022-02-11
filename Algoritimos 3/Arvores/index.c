#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

no_t *start_nodo (char value) {
    no_t *nodo;
    if ((nodo = malloc (sizeof (no_t)))) {
        nodo->value = value;
        nodo->left = NULL;
        nodo->right = NULL;
        return nodo;
    } else return NULL;
}

/* constroi um aarvore apartir de uma representação dem strings */
/* (F(B(A)(D(C)(E)))(H(G)(I))) */
no_t *mount_tree (char str[], int *pos) {
    no_t *nodo = NULL;
    if (str[*pos] == '(') {
        (*pos)++;
        printf("Cria nó: %c\n", str[*pos]);
        nodo = start_nodo (str[*pos]);
        (*pos)++;
        nodo->left = mount_tree (str, pos);
        nodo->right = mount_tree (str, pos);
        (*pos)++;
    }
    return nodo; 
}

/* ando pela arvore em ordem (Segue os slides Aula 03 - Definições de Árvores) */
void in_order (no_t *nodo) {
    if (nodo != NULL) {
        in_order (nodo->left);
        printf (" %c \n", nodo->value);
        in_order (nodo->right);
    }
}

/* conta a quantidade de nodos da arvore */
int count_nodos (no_t *nodo) {
    if (nodo != NULL) {
        return count_nodos (nodo->left) + count_nodos (nodo->right) + 1;
    } else return 0;
}

/* verifica a altura da arvore */
int tree_height (no_t *nodo) {
    int height_left, height_right;
    if (nodo == NULL) return -1;

    height_left = tree_height (nodo->left);
    height_right = tree_height (nodo->right);

    if (height_left > height_right) return height_left+1;
    else return height_right+1;
}


int main () {
    no_t *nodo;
    int pos = 0;
    char str[100]= "(F(B(A)(D(C)(E)))(H(G)(I)))";

    nodo = mount_tree (str, &pos);

    printf("Apresenta em ordem: \n");
    in_order(nodo);

    printf("Altura da arvore: %d\n", tree_height (nodo));
    printf("quantidade de nodos da arvore: %d\n", count_nodos (nodo));
    return 1;
}