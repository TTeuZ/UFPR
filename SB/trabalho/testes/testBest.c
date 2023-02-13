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

  a = alocaMem(10);
  imprimeMapa();

  // --------------
  liberaMem(b);
  imprimeMapa();

  b = alocaMem(200);
  imprimeMapa();
  // --------------

  finalizaAlocador();
  imprimeMapa();
}