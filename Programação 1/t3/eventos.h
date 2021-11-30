#include "entidades.h"
#include "liblef.h"

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

/* Eventos de criacao */
/* ------------------------------------------------------------------------------- */
/* Funcao responsavel por inicializar tudo o que for necessario para
   a simulacao do mundo */
mundo_m cria_mundo (lef_t *eventos);

/* Funcao que cria eventos de chegada em locais aleatorios do mundo */
void cria_evento_de_chegada (pessoa_m pessoa, lef_t *eventos);
/* ------------------------------------------------------------------------------- */
/* Eventos de criacao */

/* Eventos de execucao */
/* ------------------------------------------------------------------------------- */
/* função relacionada ao evento de chegada de pessoa em um local */
void evento_chegada (int id_pessoa, int id_local);

/* função relacionada ao evento de saida de pessoa em um local */
void evento_saida (int id_pessoa, int id_local);

/* função relacionada a disseminacao de rumores por uma pessoa no local */
void evento_disseminacao (int id_pessoa, int id_local, conjunto_t *cj_rumores);

/* função relacionada ao evento de fim de mundo */
void evento_fim ();
/* ------------------------------------------------------------------------------- */
/* Eventos de execucao */