#include <stdio.h>
#include <stdlib.h>
#include "eventos.h"

#define TAM_MUNDO 20000
#define RUMORES_MUNDO 30
#define PESSOAS_MUNDO 100
#define LOCAIS_MUNDO 8  
#define FIM_MUNDO 34944

/* Funções internas */
/* ------------------------------------------------------------------------------- */
/* funcao que gera um numero aleatorio entre dois limites */
int gerar_numeros_aleatorios (int min, int max) {
    return min + (rand() % max);
}

/* cria o array de rumores e o retorna em rumores */
void cria_rumores_mundo (conjunto_t rumores[]) {
    int count;
    /* Cria uma seguencia ordenada de rumores com id = count (1 a 30) */
    for (count = 1; count <= RUMORES_MUNDO; count++) 
        insere_conjunto (rumores, count);
}

/* Cria todos os locais que vão ser usados na simulacao do mundo */
void cria_locais_mundo (local_m locais[]) {
    local_m local;
    int count;
    /* Gera os locaois do mundo */
    for (count = 1; count <= LOCAIS_MUNDO; count++) {
        local.id = count;
        local.lot_max = gerar_numeros_aleatorios (5, 30); /* gera uma lotação max */
        local.localizacao.x = gerar_numeros_aleatorios (0, TAM_MUNDO-1); /* gera a posicao no eixo x */
        local.localizacao.y = gerar_numeros_aleatorios (0, TAM_MUNDO-1); /* gera a posicao no eixo xy*/
        local.pessoas = cria_conjunto (local.lot_max); /* gera o conjunto de pessoas do local */
        local.fila = cria_fila (); /* gera a lista de espera */
        /* adiciona esse local no array */
        locais[count-1] = local;
    }
}

/* cria todas as pessoas que participaram da simulacao do mundo */
void cria_pessoas_mundo (pessoa_m pessoas[], conjunto_t rumores[], lef_t *eventos) {
    pessoa_m pessoa;
    int count;
    /* gera todas as pessoas do mundo */
    for (count = 1; count <= PESSOAS_MUNDO; count++) {
        pessoa.id = count;
        pessoa.extroversao = gerar_numeros_aleatorios (0, 100); /* gera o nivel de extroversao dela */
        pessoa.paciencia = gerar_numeros_aleatorios (0, 100); /* gera o nivel de passiencia dela */
        pessoa.idade = gerar_numeros_aleatorios (18, 101); /* gera a idade dela */
        pessoa.rumores = cria_subconjunto (rumores, gerar_numeros_aleatorios (1, 5)); /* gera o conjunto de rumores dela */
        /* insere a pessoa no array */
        pessoas[count-1] = pessoa;

        cria_evento_de_chegada (pessoa, eventos, 0, 96*7);
    }
}
/* ------------------------------------------------------------------------------- */
/* Funções internas */

/* Funções de criacao */
/* ------------------------------------------------------------------------------- */
mundo_m cria_mundo (lef_t *eventos) {
    mundo_m mundo;
    mundo.tempo_atual = 0; /* seta o tempo inicial do mundo */
    mundo.n_pessoas = PESSOAS_MUNDO; /* seta o numero de pessoas do mundo */
    mundo.n_locais = LOCAIS_MUNDO; /* seta o numero de locais do mundo */
    mundo.tam_mundo.x = TAM_MUNDO; /* seta o tamanho max do eixo x do mundo */
    mundo.tam_mundo.y = TAM_MUNDO; /* seta o tamanho max do eixo y do mundo */

    mundo.rumores = cria_conjunto (RUMORES_MUNDO); /* cria o conjunto de rumores */
    cria_rumores_mundo (mundo.rumores); /* cria todos os rumores para a simulacao */
    cria_locais_mundo (mundo.locais); /* cria todos os locais para a simulacao */
    cria_pessoas_mundo (mundo.pessoas, mundo.rumores, eventos); /* cria todas as pessoas para a simulacao */

    cria_evento_de_fim (eventos);
    /* retorna o mundo criado para a main */
    return mundo;
}

/* cria os eventos de chegada iniciais para cada pessoa do mundo */
void cria_evento_de_chegada (pessoa_m pessoa, lef_t *eventos, int lim_inf, int lim_sup) {
    evento_t evento; /* evento que vai ser inserido */
    dados_chegada_m chegada_pessoa; /* dados do evento */

    chegada_pessoa.id_pessoa = pessoa.id;
    chegada_pessoa.id_local = gerar_numeros_aleatorios (0, LOCAIS_MUNDO-1);

    evento.tempo = gerar_numeros_aleatorios (lim_inf, lim_sup);
    evento.tipo = 1;
    evento.tamanho = sizeof(dados_chegada_m);
    evento.dados = &chegada_pessoa;

    adiciona_ordem_lef (eventos, &evento);
}

void cria_evento_de_fim (lef_t *eventos) {
    evento_t evento; /* evento que vai ser inserido */

    evento.tempo = 34944;
    evento.tipo = 4;
    evento.tamanho = 0;
    evento.dados = NULL;
    adiciona_ordem_lef (eventos, &evento);
}
/* ------------------------------------------------------------------------------- */
/* Funções de criacao */

/* Funções de execucao */
/* ------------------------------------------------------------------------------- */
void evento_chegada (int id_pessoa, int id_local) {
    printf("id da pessoa de chegada: %d\n", id_pessoa);
    printf("id do local: %d\n", id_local);
}

void evento_fim (mundo_m mundo) {
    int count; /* contador para os for */
    /* libera todos os rumores das pessoas */
    for (count = 0; count < mundo.n_pessoas; count++) 
        destroi_conjunto (mundo.pessoas[count].rumores);
    /* libera as pessoas dos locais e as filas */
    for (count = 0; count < mundo.n_locais; count++) {
        destroi_conjunto (mundo.locais[count].pessoas);
        destroi_fila (mundo.locais[count].fila);
    }
    /* libera os rumores do mundo */
    destroi_conjunto (mundo.rumores);
}
/* ------------------------------------------------------------------------------- */
/* Funções de execucao */