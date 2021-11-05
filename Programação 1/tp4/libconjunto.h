struct conjunto {
    int max;    /* tamanho do vetor atualmente alocado           */
    int card;   /* cardinalidade, isto eh, tamanho usado ate max */
    int *v;     /* vetor de inteiros com no maximo max elementos */
};

typedef struct conjunto conjunto_t;

/* cria um conjunto e retorna seu endereço se a operacao foi bem sucedida e 0 caso contrario */
/* o tamanho máximo do conjunto eh max */
conjunto_t * cria_conjunto (int max);

/* destroi o conjunto c liberando todo espaco previamente alocado a este conjunto */
void destroi_conjunto (conjunto_t *c);

/* retorna 1 se o conjunto c1 esta contido no conjunto c2 e 0 caso contrario */
int contido (conjunto_t *c1, conjunto_t *c2);

/* retorna a cardinalidade do conjunto c */
int cardinalidade (conjunto_t *c);

/* retorna 1 se o conjunto c eh vazio e 0 caso contrario   */
int eh_vazio (conjunto_t *c);

/* retorna 1 se o elemento n pertence ao conjunto c e 0 caso contrario   */
int pertence (int n, conjunto_t *c);

/* retorna 1 se o conjunto c1 eh igual ao conjunto c2 e 0 caso contrario */
int sao_iguais (conjunto_t *c1, conjunto_t *c2);

/* retorna o endereco do conjunto diferenca entre c1 e c2, nesta ordem  */
/* retorna 0 se a operacao falhou                                       */
conjunto_t * cria_diferenca (conjunto_t *c1, conjunto_t *c2);

/* retorna o endereco do conjunto interseccao entre os conjuntos c1 e c2  */
/* retorna 0 se a operacao falhou                                         */
conjunto_t * cria_interseccao (conjunto_t *c1, conjunto_t *c2);

/* retorna o endereco do conjunto uniao entre os conjuntos c1 e c2  */
/* retorna 0 se a operacao falhou                                   */
conjunto_t * cria_uniao (conjunto_t *c1, conjunto_t *c2);

/* insere o elemento n no conjunto c caso ele nao exista                     */
/* retorna 1 se a operacao foi bem sucedida e retorna 0 se tente inserir     */
/* elemento ja existente (conjuntos nao tem repeticao) e -1 se nao ha espaco */
int insere (int n, conjunto_t *c);

/* retira o elemento n do conjunto c caso ele exista */
/* retorna 1 se a operacao foi bem sucedida e retorna 0 se nao existe  */
int retira (int n, conjunto_t *c);

/* imprime os elementos do conjunto sempre em ordem crescente */
/* mesmo que a estrutura interna nao garanta isso             */
void imprime (conjunto_t *c);