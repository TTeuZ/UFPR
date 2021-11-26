#include <stdio.h>
#include "eventos.h"

int main () {
    pessoa_m pessoas[MAX_PESSOAS]; /* vetor para armazenar as pessoas do mundo */
    local_m locais[MAX_LOCAIS]; /* vetor para armazenar os locais do muno */
    conjunto_t *rumores; /* conujnto para armazenar os rumores do mundo */
    lef_t *eventos; /* lista de eventos proximos do mundo */

    /* Iniciamos a lista de eventos futuros do mundo */
    eventos = cria_lef ();
    /* cria o conjunto de rumores do mundo */
    rumores = cria_conjunto (MAX_RUMORES);
    /* inicializa tudo o que precimos para o mundo da simulacao */
    cria_mundo (pessoas, locais, rumores, eventos);

    printf("rumor numero 20: %d\n", rumores->v[19]);
    printf("-------------------------------------------------------");
    printf("id do 7 local = %d\n", locais[7].id);
    printf("lot_max do 7 local = %d\n", locais[7].lot_max);
    printf("localizacao x do 7 local = %d\n", locais[7].localizacao.x);
    printf("localizacao x do 7 local = %d\n", locais[7].localizacao.y);
    printf("ponteiro do conjutno do 7 local = %p\n", locais[7].pessoas);
    printf("ponteiro da fila do 7 local = %p\n", locais[7].fila);
    printf("-------------------------------------------------------");
    printf("id do 7 pessoas = %d\n", pessoas[7].id);
    printf("extroversao do 7 pessoas = %d\n", pessoas[7].extroversao);
    printf("paciencia do 7 pessoas = %d\n", pessoas[7].paciencia);
    printf("idade do 7 pessoas = %d\n", pessoas[7].idade);
    imprime (pessoas[7].rumores);
    return 1;
}