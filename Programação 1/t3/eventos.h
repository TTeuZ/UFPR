#include "entidades.h"
#include "liblef.h"

#define TAM_MUNDO 20000
#define RUMORES_MUNDO 30
#define PESSOAS_MUNDO 100
#define LOCAIS_MUNDO 8  
#define FIM_MUNDO 34944

/* define os nomes para os cases do mundo */
#define CS_CHEGADA 1
#define CS_SAIDA 2
#define CS_DISCEMINACAO 3
#define CS_FIM 4

/* struct com os dados do evento de chegada */
typedef struct dados_chegada {
    int id_pessoa;
    int id_local;
} dados_chegada_m; 

/* struct com os dados do evento de saida*/
typedef struct dados_saida {
    int id_pessoa;
    int id_local;
} dados_saida_m;

/* struct com os dados do evento de disceminacao */
typedef struct dados_disceminacao {
    conjunto_t *cj_rumores;
    int id_pessoa_origem;
    int id_local;
} dados_disceminacao_m;

/* Funcoes de criacao */
/* ------------------------------------------------------------------------------- */
/* Funcao responsavel por inicializar tudo o que for necessario para
   a simulacao do mundo */
mundo_m cria_mundo (lef_t *eventos);

/* Funcao que cria eventos de chegada em locais aleatorios do mundo */
void cria_evento_de_chegada (pessoa_m pessoa, local_m local, lef_t *eventos, int tempo);

/* Funcao que cria eventos de saida de locais*/
void cria_evento_de_saida (pessoa_m pessoa, local_m local, lef_t *eventos, int tempo);

/* Funcao que cria eventos de disceminacao*/
void cria_evento_de_disceminacao (pessoa_m pessoa, local_m local, lef_t *eventos, int tempo);

/* Funcao que cria o evento de fim do mundo */
void cria_evento_de_fim (lef_t *eventos);
/* ------------------------------------------------------------------------------- */
/* Funcoes de criacao */

/* Funcoes de execucao */
/* ------------------------------------------------------------------------------- */
/* funcao relacionada ao evento de chegada de pessoa em um local */
void evento_chegada (mundo_m mundo, lef_t *eventos, int id_pessoa, int id_local);

/* funcao relacionada ao evento de saida de pessoa em um local */
void evento_saida (mundo_m mundo, lef_t *eventos, int id_pessoa, int id_local);

/* funcao relacionada a disseminacao de rumores por uma pessoa no local */
void evento_disseminacao (mundo_m mundo, int id_pessoa, int id_local, conjunto_t *cj_rumores);

/* funcao relacionada ao evento de fim de mundo */
void evento_fim (mundo_m mundo);
/* ------------------------------------------------------------------------------- */
/* Funcoes de execucao */