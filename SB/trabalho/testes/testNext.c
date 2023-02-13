#include <stdio.h>
#include "malloc.h"

int main() {
    void* a, * b, * c;
    iniciaAlocador();
    imprimeMapa();

    a = alocaMem(30);
    imprimeMapa();

    b = alocaMem(40);
    imprimeMapa();

    c = alocaMem(50);
    imprimeMapa();

    liberaMem(a);
    imprimeMapa();

    liberaMem(b);
    imprimeMapa();

    liberaMem(c);
    imprimeMapa();

    a = alocaMem(35);
    imprimeMapa();

    b = alocaMem(40);
    imprimeMapa();

    finalizaAlocador();
    imprimeMapa();
}