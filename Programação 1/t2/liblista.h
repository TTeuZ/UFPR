/*
 * TAD lista
 * Autores:
 *    Marcos Alexandre Castilho
 *    Luis Carlos Erpen de Bona
 *
 * Primeira versão em 18/10/2019
 * Versao 1.0.0 de 10/11/2021
*/

struct nodo {
    int elemento;          /* lista de numeros inteiros               */
    struct nodo *prox;  /* ponteiro para o proximo (obrigatorio)   */
    struct nodo *prev;  /* ponteiro para o anterior (uso opcional) */
};
typedef struct nodo nodo_t;

struct lista {
    nodo_t *ini;        /* ponteiro para o inicio da lista (obrigatorio)        */
    nodo_t *fim;        /* ponteiro para o fim da lista (uso opcional)          */
    int tamanho;        /* tamanho da lista (numero de elementos na lista)      */
};
typedef struct lista lista_t;

/*
 * Cria uma lista vazia e a retorna, se falhar retorna NULL.
*/
lista_t * cria_lista ();

/*
 * Remove todos os elementos da lista, libera espaco e retorna NULL.
*/
lista_t * destroi_lista (lista_t *l);

/*
 * Retorna 1 se a lista esta vazia e 0 caso contrario.
*/
int lista_vazia (lista_t *l);

/*
 * Retorna o tamanho da lista, isto eh, o numero de elementos presentes nela.
*/
int tamanho_lista (lista_t *l);

/*
 * Insere o elemento no inicio da lista.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
*/
int insere_inicio_lista (lista_t *l, int elemento);

/*
 * Insere o elemento no final da lista.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
*/
int insere_fim_lista (lista_t *l, int elemento);

/*
 * Insere o elemento na lista garantindo ordenacao em ordem crescente.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
*/
int insere_ordenado_lista (lista_t *l, int elemento);

/*
 * Remove o elemento do inicio da lista e o retorna em 'elemento'.
 * Retorna o elemento.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
*/
int retira_inicio_lista (lista_t *l, int *elemento);

/*
 * Remove o elemento do final da lista e o retorna em 'elemento'.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
*/
int retira_fim_lista (lista_t *l, int *elemento);

/*
 * Remove o elemento 'elemento' caso ele exista na lista.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 * Se o elemento nao for encontrado na lista tambem retorna 0.
*/
int retira_elemento_lista (lista_t *l, int elemento);

/*
 * Retorna 1 se o elemento existe na lista e 0 caso contrario.
*/
int pertence_lista (lista_t *l, int elemento);
