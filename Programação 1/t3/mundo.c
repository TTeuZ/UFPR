#include <stdio.h>
#include "eventos.h"

int main () {
    mundo_m mundo; /* variavel que vai receber o mundo criado para a simulacao */
    lef_t *eventos; /* lista de eventos proximos do mundo */

    /* Iniciamos a lista de eventos futuros do mundo */
    eventos = cria_lef ();
    /* inicializa tudo o que precimos para o mundo da simulacao */
    mundo = cria_mundo (eventos);
    return 1;
}