// Este programa testa a função recursiva maximo,
// que calcula um elemento máximo de um vetor.
//////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
int maximo (int n, int v[]);

#define N 10000

int main (void)
{
   int v[N], n;

   printf ("\nNúmero de elementos: ");
   scanf ("%d", &n);
   if (n < 1 || n > N) {
      printf ("Sequência vazia ou muito grande\n");
      return EXIT_FAILURE;
   }
   printf ("Elementos:\n");
   for (int i = 0; i < n; ++i) 
      scanf ("%d", &v[i]);
   int x = maximo (n, v);
   printf ("máximo: %d\n", x);
   return EXIT_SUCCESS;
}

int maximo (int n, int v[]) { 
   if (n == 1) return v[0];
   int x = maximo (n-1, v);
   if (x > v[n-1]) return x;
   else return v[n-1]; 
}