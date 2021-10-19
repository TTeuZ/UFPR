#include "biblioteca.h"

/* -------------------------------------------------------------------------- */
/* devolve o índice de um elemento mínimo em v[a..b] */

static unsigned int minimo(int v[], unsigned int a, unsigned int b) {

  unsigned int i, 
    m = a;

  for (i=a+1; i<=b; ++i)
    if ( compara(v[i],v[m]) < 0 )
      m = i;

  return m;
}
/* -------------------------------------------------------------------------- */
/* ordena v[a..b] pelo método da seleção e devolve v */

int *selecao(int v[], unsigned int a, unsigned int b) {

  if ( a >= b )
    return v;

  troca(v,a,minimo(v,a,b));

  return selecao(v, a+1, b);
}
