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
        /* atualiza o tempo do mundo */
        mundo.tempo_atual = mundo.tempo_atual + ev_atual->tempo;

        /* switch para os possiveis casos */
        switch (ev_atual->tipo) {
            /* caso para o evento de chegada */
            case 1: {
                /* faz o cast correto dos dados do evento */
                ev_dados_chegada = (dados_chegada_m*)ev_atual->dados;
                /* chama o evento de chegada */
                evento_chegada (mundo, eventos, ev_dados_chegada->id_pessoa,ev_dados_chegada->id_local);
                /* libera as estruturas do evento */
                free (ev_atual->dados);
                free (ev_atual);
                break;
            }
            /* caso para o evento de saida */
            case 2: { 
                printf("entramo na saida\n");
                free (ev_atual->dados);
                free (ev_atual);
                break;
            }
            /* caso para o evento de disceminacao */
            case 3: {
                printf("entramo na fofoca\n");
                free (ev_atual->dados);
                free (ev_atual);
                break;
            }
            /* caso para o evento de fim */
            case 4: {
                free (ev_atual->dados);
                free (ev_atual);
                evento_fim (mundo);
                break;
            }
        }
    }
    destroi_lef (eventos); /* libera a LEF */
    return 1;
}