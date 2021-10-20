#include "particiona.h"
#include "biblioteca.h"

#include <time.h>
#include <stdlib.h>

/* -------------------------------------------------------------------------- */
/* devolve a mediana de a, b e c                                              */

static int mediana(int a, int b, int c) {
  if (compara(a, b) == 1) {
    if (compara(a, c) == 1) return a;
    return c;
  } else {
    if (compara(b, c) == 1) return b;
    return c;
  }
}

/* -------------------------------------------------------------------------- */
/* Retorna o posição da mediana encontrada*/

int correct_position(int v[], int pivo, int a, int b, int c) {
  if (compara(pivo, v[a]) == 0) {
    return a;
  } else if (compara(pivo, v[b]) == 0) {
    return b;
  } else {
    return c;
  }
}

/* -------------------------------------------------------------------------- */
/* ordena v[a..b]  usando o algoritmo  "QuickSort com mediana de  3" e
   devolve v                                                                  */

int *quicksort_mediana(int v[], int a, int b) {
  if (a >= b) return v;

  int rand_one, rand_two, rand_three; 
  int pivo, pos;

  if(b-a+1 >= 3) {
    srand(time(0));
    rand_one = (rand() % ((b-a+1))) + a;
    rand_two = (rand() % ((b-a+1))) + a;
    rand_three = (rand() % ((b-a+1))) + a;

    pivo = mediana(v[rand_one], v[rand_two], v[rand_three]);
    pos = correct_position(v, pivo, rand_one, rand_two, rand_three);

    troca(v,pos,b);
  }

  int m = particiona(v, a, b, v[b]);
  quicksort_mediana(v, a, m-1);
  quicksort_mediana(v, m+1, b);
  return v;
}



