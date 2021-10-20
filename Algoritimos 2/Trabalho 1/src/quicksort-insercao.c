#include "insercao.h"
#include "particiona.h"


/* -------------------------------------------------------------------------- */
/* ordena v[a..b] usando o algoritmo QuickSort com inser��o e devolve v       */

int *quicksort_insercao(int v[], int a, int b, unsigned int m) {
  if (a >= b) return v;
  int particionador = particiona(v, a, b, v[b]);

  if (m >= (b-a+1)) {
    insercao(v, a, b);
  } else {
    quicksort_insercao(v, a, particionador-1, m);
    quicksort_insercao(v, particionador+1, b, m);
  }
  return v;
}
