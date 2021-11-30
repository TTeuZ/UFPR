#include <stdio.h>
#include <stdlib.h>
#include "eventos.h"

int main () {
    mundo_m mundo; /* variavel que vai receber o mundo criado para a simulacao */
    lef_t *eventos; /* lista de eventos proximos do mundo */
    evento_t *ev_atual; /* variavel que vai receber o evento atual */
    dados_chegada_m *ev_dados_chegada; /* ponteiro que vai receber os dados de chegada */

    /* Iniciamos a lista de eventos futuros do mundo */
    eventos = cria_lef ();
    /* inicializa tudo o que precimos para o mundo da simulacao */
    mundo = cria_mundo (eventos);

    /* while para executar os eventos */
    while ((ev_atual = obtem_primeiro_lef (eventos)) != NULL) {
        mundo.tempo_atual = mundo.tempo_atual + ev_atual->tempo;

        ev_dados_chegada = (dados_chegada_m*)ev_atual->dados;

        printf("id da pessoa de chegada: %d\n", ((dados_chegada_m*)ev_dados_chegada)->id_pessoa);

        /* switch para os possiveis casos */
        switch (ev_atual->tipo) {
            /* caso para o evento de chegada */
            case 1: { 
                /* ev_dados_chegada = (dados_chegada_m*)ev_atual->dados;
                printf("id da pessoa de chegada: %d\n", ((dados_chegada_m*)ev_atual->dados)->id_pessoa); */
                /* printf("id do local: %d\n", ((dados_chegada_m*)ev_atual->dados)->id_local); */
                /* evento_chegada (ev_dados_chegada->id_pessoa, ev_dados_chegada->id_local);
                free (ev_atual); */
                break;
            }
            /* caso para o evento de saida */
            case 2: { 
                break;
            }
            /* caso para o evento de disceminacao */
            case 3: {
                break;
            }
            /* caso para o evento de fim */
            case 4: {
                break;
            }
        }
    }

    return 1;
}