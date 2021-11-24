/* Implementa o TAD Lista de Eventos Futuros (LEF) 
 * Feito em C para a disciplina CI1001 - Programacao 1 no dia 10/11/2021
 * Autor: Luis C. E. Bona 
 *
 * Versao 1.0.0
*/

/*
 * evento_t possui membros comuns a todos eventos e um membro
 * dados para armazenar as estruturas especificas de cada evento 
*/
typedef  struct evento {
	int tempo;   /* tempo logico do evento */
	int tipo;    /* inteiro para diferenciar os diferentes tipos de evento */
	int tamanho; /* tamanho ocupado pela estrutura referente ao evento */
	void *dados; /* estrutura de dados descreveno o evento */
} evento_t;

/*
 * nodo_t eh uma estrutura interna que representa cada nodo da LEF.
 * Externamente o usuario da biblioteca nao vai receber essa estrutura para 
 * evitar acesso direto ao ponteiro prox.
*/
typedef struct nodo_lef {
   evento_t *evento;
   struct nodo_lef *prox;
} nodo_lef_t;

/*
 * Representacao da LEF 
*/
typedef struct lef {
   nodo_lef_t  *Primeiro;
} lef_t;

/* 
 * Cria uma LEF vazia 
*/
lef_t * cria_lef ();

/* 
 * Destroi a LEF, sempre retorna NULL. 
 * Note que nao eh possivel desalocar estruturas dentro de evento->dados se existirem 
*/ 
lef_t * destroi_lef (lef_t *l);

/* 
 * Adiciona um evento na primeira posicao da LEF. Uma nova copia
 * da estrutura evento sera feita .
*/ 
int adiciona_inicio_lef (lef_t *l, evento_t *evento);

/* 
 * Adiciona um evento de acordo com o valor evento->tempo na LEF. 
 * Uma nova copia da estrutura evento sera feita 
*/
void adiciona_ordem_lef  (lef_t *l, evento_t *evento);

/* 
 * Retorna o primeiro evento da LEF. A responsabilidade por desalocar
 * a memoria associado eh de quem chama a funcao 
*/
evento_t * obtem_primeiro_lef (lef_t *l);
