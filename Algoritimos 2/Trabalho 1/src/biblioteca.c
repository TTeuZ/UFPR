#include <stdlib.h>

static unsigned int n_comparacoes = 0, /* número de comparações */
  n_trocas = 0;                        /* número de trocas      */

/* -------------------------------------------------------------------------- */
void zera_contadores(void) {

  n_comparacoes = n_trocas = 0;
}
/* -------------------------------------------------------------------------- */
unsigned int total_trocas(void) {

  return n_trocas;
}
/* -------------------------------------------------------------------------- */
unsigned int total_comparacoes(void) {

  return n_comparacoes;
}
/* -------------------------------------------------------------------------- */
/* devolve -1, 0 ou 1 conforme a < b, a = b ou a > b, respectivamente,        */
/* e soma 1 a n_comparacoes                                                   */

int compara(int a, int b) {
  
  ++n_comparacoes;

  if ( a < b )
    return -1;

  if ( a > b )
    return 1;

  return 0;
}
/* -------------------------------------------------------------------------- */
/* troca v[a] e v[b] entre si                                                 */
/* e soma 1 a n_trocas                                                        */

void troca(int v[], unsigned int a, unsigned int b) {

  int aux = v[a];
  
  v[a] = v[b];
  v[b] = aux;

  ++n_trocas;
}
/* -------------------------------------------------------------------------- */
/* devolve um int pseudo-aleatório entre min e max, inclusives                */

int sorteia(int min, int max) {
  
  return min + (rand() % (max-min+1));
}
