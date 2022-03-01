typedef struct nodo {
    int value;
    int height;
    struct nodo *left, *right, *father;
} nodo_t;

typedef struct tree {
    nodo_t *root;
    int nodos_qtd;
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
* o primeiro valor a chava do nodo e o segundo o seu nivel
*/ 
void in_order (tree_t *tree, nodo_t *nodo, int nivel);

/*
* Função que executa a busca do valor na ALV
* retorna NULL caso o valor não exista, ou o nodo no qual o valor é a chave
*/ 
nodo_t *search_tree (nodo_t *nodo, int value);

/*
* Função de rotação do nodo selecionado para a esquerda em relação ao seu filho da direita
* O nodo a ser enviado é o pai do nodo o qual voce deseja rotacionar
* Atualiza as alturas caso necessário
*/ 
nodo_t *left_rotate_tree (tree_t *tree, nodo_t *nodo, int d_value);

/*
* Função de rotação do nodo selecionado para a direita em relação ao seu filho da esquerda
* O nodo a ser enviado é o pai do nodo o qual voce deseja rotacionar
* Atualiza as alturas caso necessário
*/ 
nodo_t *right_rotate_tree (tree_t *tree, nodo_t *nodo, int d_value);

/*
* Função de inserção de valor nas folhas da arvore
* apos a inserção, verifica o balanceamento d arvore e a ajusta.
*/ 
nodo_t *insert_in_leave (tree_t *tree, nodo_t *nodo, int value);

/*
* Função que busca o antecessor do nodo indicado.
*/ 
nodo_t *predecessor (nodo_t *nodo);

/*
* Função que realiza a troca do nodo 'removed' pelo nodo 'transplanted', removendo os acessos
* ao nodo 'removed', o removendo da arvore.
*/ 
void nodo_transplant (tree_t *tree, nodo_t *removed, nodo_t *transplanted);

/*
* Função que remove o nodo da avore a partir de um transplante
* Executa as verificações de balanceamento apos a remoção
*/ 
void transplant_nodo_delete (tree_t *tree, nodo_t *nodo);