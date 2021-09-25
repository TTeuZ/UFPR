// Ao receber v e n >= 1, a função devolve
// o valor de um elemento máximo do
// vetor v[0..n-1].
#include <stdio.h>

// tipo 1
int maximo (int n, int v[])
{ 
   if (n == 1)
      return v[0];
   else {
      int x;
      x = maximo (n-1, v);
      // x é o máximo de v[0..n-2] 
      if (x > v[n-1]) return x;
      else return v[n-1]; 
   }
}

// v2
int maximo2 (int n, int v[]) {
   int x;
   if (n == 1) x = v[0];
   else {
      x = maximo (n-1, v); 
      if (x < v[n-1]) x = v[n-1];
   }
   return x;
}

// v3
int maximo3 (int n, int v[]) { 
   if (n == 1) return v[0];
   int x = maximo3 (n-1, v);
   if (x > v[n-1]) return x;
   else return v[n-1]; 
}

void main (int argc, char *argv[]) {
    int v[] = {12, 14, 9, 2, 10};
    int n = 5;
    printf ("%d \n", maximo(n, v));
    printf ("%d \n", maximo2(n, v));
    printf ("%d \n", maximo3(n, v));
}
