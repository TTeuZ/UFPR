#include <stdio.h>
#include <stdlib.h>
int maximo (int n, int v[]);
int minimo (int n, int v[]);

void main (int argc, char *argv[]) {
    int v[100], n;
    printf("Número de elements: %d\n", n);
    scanf("%d", &n);
    printf("Elementos: \n");
    for (int i = 0; i < n; ++i)
        scanf("%d", &v[i]);
    printf("maximo: %d \n", maximo(n, v));
    printf("minimo: %d \n", minimo(n, v));
}
int maximo (int n, int v[]) { 
   if (n == 1) return v[0];
   int x = maximo (n-1, v);
   if (x > v[n-1]) return x;
   else return v[n-1]; 
}
int minimo (int n, int v[]) { 
   if (n == 1) return v[0];
   int x = minimo (n-1, v);
   if (x < v[n-1]) return x;
   else return v[n-1]; 
}