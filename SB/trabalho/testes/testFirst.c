#include <stdio.h>
#include "malloc.h"

int main() {
    void* a, * b;
    iniciaAlocador();
    imprimeMapa();

    a = alocaMem(32);
    imprimeMapa();

    b = alocaMem(30);
    imprimeMapa();

    liberaMem(a);
    imprimeMapa();

    liberaMem(b);
    imprimeMapa();

    a = alocaMem(20);
    imprimeMapa();

    finalizaAlocador();
    imprimeMapa();
}