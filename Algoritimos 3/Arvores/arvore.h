#include <stdio.h>

typedef struct nodo {
    char value;
    struct nodo *left;
    struct nodo *right;
} no_t;

no_t *start_nodo (char value);

no_t *mount_tree (char str[], int *pos);

void in_order (no_t *nodo);

int count_nodos (no_t *nodo);

int tree_height (no_t *nodo);