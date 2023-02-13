#include <stdio.h>
#include "malloc.h"

int main() {
    void* a, * b;
    iniciaAlocador();
    imprimeMapa();

    a = alocaMem(32);
    imprimeMapa();

    b = alocaMem(50);
    imprimeMapa();

    liberaMem(a);
    imprimeMapa();

    liberaMem(b);
    imprimeMapa();

    b = alocaMem(10);
    imprimeMapa();

    // --------------
    liberaMem(b);
    imprimeMapa();

    b = alocaMem(200);
    imprimeMapa();

    a = alocaMem(20);
    imprimeMapa();
    // --------------

    finalizaAlocador();
    imprimeMapa();
}