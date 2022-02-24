typedef struct nodo {
    int value;
    int height;
    struct nodo *left, *right, *father;
} nodo_t;

typedef struct tree {
    nodo_t *root;
    int nodos_qtd, height;
} tree_t;

/*
* Função que inicia a arvore, alocando espaço para armazenar suas informações
* setando os valores iniciais entre 0 e NULL
*/ 
tree_t *create_tree ();

/*
* Função que inicia um nodo alocando espaço para armazenar suas informações,
* setando seu svalores iniciais entre 0 e Null
*/ 
nodo_t *create_nodo (int value);

/*
* Função que lé a AVL de maneira ordenada
* o retorno é formatado para exibir cada valor em uma linha, sendo
* o primeiro valor a chava do nodo e o segundo a sua altura
*/ 
void in_order (nodo_t *nodo);

/*
* Função que executa a busca do valor na ALV
* retorna NULL caso o valor não exista, ou o nodo no qual o valor é a chave
*/ 
nodo_t *search_tree (nodo_t *nodo, int value);

/*
* Função de rotação do nodo selecionado para a esquerda em relação ao seu filho da direita
* O nodo a ser enviado é o pai do nodo o qual voce deseja rotacionar
*/ 
void left_rotate_tree (tree_t *tree, nodo_t *nodo);

/*
* Função de rotação do nodo selecionado para a direita em relação ao seu filho da esquerda
* O nodo a ser enviado é o pai do nodo o qual voce deseja rotacionar
*/ 
void right_rotate_tree (tree_t *tree, nodo_t *nodo);

/*
* Função de inserção de valor nas folhas da arvore
*/ 
nodo_t *insert_in_leave (tree_t *tree, nodo_t *nodo, int height, int value);

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