/*
 * TAD fila
 * Autores:
 *    Marcos Alexandre Castilho
 *    Luis Carlos Erpen de Bona
 *
 * Primeira versão em 18/10/2019
 * Versao 1.0.0 de 10/11/2021
*/

struct nodo_f {
    int chave;          /* lista de numeros inteiros               */
    struct nodo_f *prox;  /* ponteiro para o proximo (obrigatorio)   */
    struct nodo_f *prev;  /* ponteiro para o anterior (uso opcional) */
};
typedef struct nodo_f nodo_f_t;

struct fila {
    nodo_f_t *ini;        /* ponteiro para o inicio da lista (obrigatorio)       */
    nodo_f_t *atual;      /* ponteiro para algum elemento da lista (obrigatorio) */
    nodo_f_t *fim;        /* ponteiro para o fim da lista (uso opcional)         */
    int tamanho;        /* tamanho da lista (numero de elementos na lista)     */
};
typedef struct fila fila_t;

/*
 * Cria uma fila vazia e a retorna, se falhar retorna NULL.
*/
fila_t * cria_fila ();

/*
 * Remove todos os elementos da fila, libera espaco e devolve NULL.
*/
fila_t * destroi_fila (fila_t *f);

/*
 * Retorna 1 se a fila esta vazia e 0 caso contrario.
*/
int fila_vazia (fila_t *f);

/*
 * Retorna o tamanho da fila, isto eh, o numero de elementos presentes nela.
*/
int tamanho_fila (fila_t *f);

/*
 * Insere o elemento no final da fila (politica FIFO).
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
*/
int insere_fila (fila_t *f, int elemento);

/*
 * Remove o elemento do inicio da fila (politica FIFO) e o retorna.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
*/
int retira_fila (fila_t *f, int *elemento);

/*
 * As funcoes abaixo permitem quebrar a politica FIFO da fila,
 * Permite acesso a elementos apontados pelo ponteiro 'atual'.
 * Este ponteiro pode ser inicializado e incrementado, viabilizando
 * a implementacao de um mecanismo iterador.
*/

/*
 * Inicializa o ponteiro atual para o primeiro elemento da fila.
 * Retorna 1 se a operacao foi bem sucedida e zero caso contrario.
*/
int inicializa_atual_fila (fila_t *f);

/*
 * Faz o ponteiro atual apontar para o próximo nodo da fila f.
*/
void incrementa_atual_fila (fila_t *f);

/*
 * Retorna em *elemento o valor contido na chave apontada pelo ponteiro atual. 
 * Se atual não for válido a função retorna zero senão retorna 1.
*/
int consulta_atual_fila (fila_t *atual, int *elemento);

/*
 * Remove o elemento apontado por atual da fila f e o retorna em *elemento.
 * Faz o atual apontar para o sucessor do nodo removido.
 * Retorna 1 se houve sucesso e zero caso contrario.
*/
int retira_atual_fila (fila_t *f, int *elemento);
