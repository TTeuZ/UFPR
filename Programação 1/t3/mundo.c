#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "eventos.h"

int main () {
    int fim_mundo = 0; /* variavel que sinaliza que o evento de fim foi chamado */
    mundo_m mundo; /* variavel que vai receber o mundo criado para a simulacao */
    lef_t *eventos; /* lista de eventos proximos do mundo */
    evento_t *ev_atual; /* variavel que vai receber o evento atual */
    dados_chegada_m *ev_dados_chegada; /* ponteiro que vai receber os dados de chegada */
    dados_saida_m *ev_dados_saida; /* ponteiro que vai receber os dados de saida */
    dados_disceminacao_m *ev_dados_disceminacao; /* ponteiro que vai receber os dados de disceminacao */

    /* Iniciamos a lista de eventos futuros do mundo */
    eventos = cria_lef ();
    /* inicializa tudo o que precimos para o mundo da simulacao */
    mundo = cria_mundo (eventos);
    /* while para executar os eventos */
    while ((ev_atual = obtem_primeiro_lef (eventos)) != NULL) {
        /* atualiza o tempo do mundo */
        mundo.tempo_atual = ev_atual->tempo;

        /* switch para os possiveis casos */
        switch (ev_atual->tipo) {
            /* caso para o evento de chegada */
            case CS_CHEGADA: {
                /* faz o cast correto dos dados do evento */
                ev_dados_chegada = (dados_chegada_m*)ev_atual->dados;
                /* verifica se o fim do mundo ja nao foi chamado */
                if (fim_mundo == 0) {
                    /* chama o evento de chegada */
                    evento_chegada (mundo, eventos, ev_dados_chegada->id_pessoa,ev_dados_chegada->id_local);
                }
                /* libera as estruturas do evento */
                free (ev_dados_chegada);
                free (ev_atual);
                break;
            }
            /* caso para o evento de saida */
            case CS_SAIDA: { 
                /* faz o cast correto dos dados do evento */
                ev_dados_saida = (dados_saida_m*)ev_atual->dados;
                 /* verifica se o fim do mundo ja nao foi chamado */
                if (fim_mundo == 0) {
                    /* chama o evento de saida */
                    evento_saida (mundo, eventos, ev_dados_saida->id_pessoa,ev_dados_saida->id_local);
                }
                /* libera as estruturas do evento */
                free (ev_dados_saida);
                free (ev_atual);
                break;
            }
            /* caso para o evento de disceminacao */
            case CS_DISCEMINACAO: {
                /* faz o cast correto dos dados do evento */
                ev_dados_disceminacao = (dados_disceminacao_m*)ev_atual->dados;
                /* verifica se o fim do mundo ja nao foi chamado */
                if (fim_mundo == 0) {
                     /* chama o evento de dsiceminacao */
                    evento_disseminacao (mundo, ev_dados_disceminacao->id_pessoa_origem, ev_dados_disceminacao->id_local, ev_dados_disceminacao->cj_rumores);
                }
                /* libera as estruturas do evento */
                destroi_conjunto (ev_dados_disceminacao->cj_rumores);
                free (ev_dados_disceminacao);
                free (ev_atual);
                break;
            }
            /* caso para o evento de fim */
            case CS_FIM: {
                free (ev_atual->dados);
                free (ev_atual);
                fim_mundo = 1;
                evento_fim (mundo);
                break;
            }
        }
    }
    destroi_lef (eventos); /* libera a LEF */
    return 1;
}