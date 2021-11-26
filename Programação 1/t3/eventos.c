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

    for (count = 1; count <= PESSOAS_MUNDO; count++) {
        pessoa.id = count;
        pessoa.extroversao = gerar_numeros_aleatorios (0, 100);
        pessoa.paciencia = gerar_numeros_aleatorios (0, 100);
        pessoa.idade = gerar_numeros_aleatorios (18, 100);
        pessoa.rumores = cria_subconjunto (rumores, gerar_numeros_aleatorios (1, 5));
    
        pessoas[count-1] = pessoa;
    }
}
/* ------------------------------------------------------------------------------- */
/* Funções internas */

/* Funções externas */
/* ------------------------------------------------------------------------------- */
void cria_mundo (pessoa_m pessoas[], local_m locais[], conjunto_t rumores[], lef_t *eventos) {
    cria_rumores_mundo (rumores);
    cria_locais_mundo (locais);
    cria_pessoas_mundo (pessoas, rumores, eventos);
}
/* ------------------------------------------------------------------------------- */
/* Funções externas */