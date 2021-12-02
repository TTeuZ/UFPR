#include "libconjunto.h"
#include "libfila.h"

/* definindo os max do mundo */
#define MAX_PESSOAS 100
#define MAX_LOCAIS 8
#define MAX_RUMORES 30

/* 
* Struct para armazenar as coordenadas que serão utilizadas pelas pessoas e pelo mundo 
*/
typedef struct coordenada {
    int x; /* posicao x da coordenada */
    int y; /* posicao y da coordenada */
} coordenada_m;

/*
* Struct para representar as pessoas do mundo
*/
typedef struct pessoa {
    int id; /* id da pessoa */
    int extroversao; /* valor de 0 a 100 que indica o grau de extroversao da pessoa */
    int paciencia; /* valor de 0 a 100 que indica o grau de paciencia da pessoa */
    int idade; /* valor de 18 a 100 que indica a idade da pessoa */
    conjunto_t *rumores; /* conjunto de rumores que a pessoa possui */
} pessoa_m;

/*
* Struct para representar os locais do mundo
*/
typedef struct local {
    int id; /* id do local */
    int lot_max; /* numero max de pessoas para o local */
    conjunto_t *pessoas; /* pessoas que estao no lugar */
    fila_t *fila; /* fila de pessoas que querem entrar no lugar */
    coordenada_m localizacao; /* coordenadas do lugar */
} local_m;

/*
* Struct para representar o mundo que vamos criar
*/
typedef struct mundo {
    int tempo_atual; /* tempo atual do mundo */
    pessoa_m pessoas[MAX_PESSOAS]; /* vetor com todas as pessaos pertencentes ao mundo */
    local_m locais[MAX_LOCAIS]; /* vetor que contem todos os locais */
    conjunto_t *rumores; /* vetor que armazena todos os rumores do mundo */
    int n_pessoas; /* variavel com o numero de pessoas do mundo */
    int n_locais; /* variavel com o numero de locais do mundo */
    coordenada_m tam_mundo; /* coordenadas maximas do mundo */
} mundo_m;

/*
* Nao existe uma estrutura para o rumor, pois ele eh apenas sera um conjunto de inteiros apenas.
* a intencao de usar o tad conjuto vem do motivo da criacao de subconjuntos para as pessoas.
*/