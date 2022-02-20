typedef struct nodo {
    int value;
    struct nodo *left;
    struct nodo *right;
    struct nodo *father;
} nodo_t;

typedef struct tree {
    nodo_t *root;
    int nodos_qtd;
    int height;
} tree_t;

/*
* Função que inicia a arvore
*/ 
tree_t *create_tree ();

/*
* Função que inicia um nodo setando seu s valores para null.
*/ 
nodo_t *create_nodo (int value);

/*
* Função de inserção de valor nas folhas da arvore
*/ 
nodo_t *insert_in_leave (tree_t *tree, nodo_t *nodo, int value);

/*
* Função que rotaciona o nodo enviado para a esquerda
*/ 
void left_rotate_tree (tree_t *tree, nodo_t *nodo);

/*
* Função que rotaciona o nodo enviado para a direita
*/ 
void right_rotate_tree (tree_t *tree, nodo_t *nodo);

/*
* Função que pega a altura da BST a partir do nodo enviado, ou seja,
* pega a altura da arvore inteira ou a partir de subarvores.
*/ 
int tree_height (nodo_t *nodo);

/*
* Função que busca o valor minimo da arvore a partir do nodo enviado.
*/ 
nodo_t *tree_minimum (nodo_t *nodo);

/*
* Função que realiza a troca do nodo pelo selecionado, removendo o trocado da arvore.
*/ 
void nodo_transplant (tree_t *tree, nodo_t *removed, nodo_t *transplanted);

/*
* Função que remove o nodo da avore a partir de um transplante
*/ 
void transplant_nodo_delete (tree_t *tree, nodo_t *nodo);

/*
* Função que lé a BST de maneira ordenada
*/ 
void in_order (nodo_t *nodo);

/*
* Função de busca na BST
*/ 
nodo_t *search_tree (nodo_t *nodo, int value);
