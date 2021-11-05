#include <stdio.h>
#include <stdlib.h>
#include "libconjunto.h"

void main () {
    int *vet, *vet_ex;
    /* Testando as possibilidades de criações de vetores com valor passando do max
     e valor coerente */
    printf("Testando a criação de vetores...\n");
    *vet_ex = cria_conjunto(103);
    printf("O conjunto com valor maior que o max retornou: %p\n", vet_ex);
    *vet = cria_conjunto(102);
    printf("O conjunto com valor dentro do limite retornou: %p\n", vet);
}