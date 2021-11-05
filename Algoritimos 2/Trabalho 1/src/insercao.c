#include "biblioteca.h"

/* -------------------------------------------------------------------------- */
/* Encontra a posição do elemento, indicando aonde ele deveria estar posicionado
no array ordenado. */

int find(int x,int v[], int a, int b) {
    if (a > b) return a-1;
    if (compara(x, v[b]) >= 0) return b;
    return find(x, v, a, b-1);
}

/* -------------------------------------------------------------------------- */
/* Insere o elemento na posição que ele deveria estar no array */

int *insert(int v[], int a, int b) {
    int p = find(v[b], v, a, b-1);
    int i = b;
    while (i > p + 1) {
      troca(v, i, i-1);
      i--;
    }
    return v;
}

/* -------------------------------------------------------------------------- */
/* ordena v[a..b] pelo m�todo da sele��o e devolve v */

int *insercao(int v[], unsigned int a, unsigned int b) {
  if (a >= b) return v;
  insercao(v, a, b-1);
  insert(v, a, b);
}
