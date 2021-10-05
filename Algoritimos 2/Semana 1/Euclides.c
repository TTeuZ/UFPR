#include <stdio.h>
// int euclides (int first, int second, int divisor);
int euclides (int first, int second);

void main (int argc, char *argv[]) {
    int first, second;
    printf ("Digite o primeiro numero: \n");
    scanf ("%d", &first);
    printf ("Digite o segundo numero: \n");
    scanf ("%d", &second);

    // printf("MDC: %d \n", euclides(first, second, 1));
    printf("MDC: %d \n", euclides(first, second));
}

// int euclides (int first, int second, int divisor) {
//     if (divisor == 0) first;
//     else {
//         divisor = first % second;
//         second = divisor;
//         first = euclides(first, second, divisor);
//     }
// }

int euclides (int m, int n) {
   int r;
   do {
      r = m % n; 
      m = n; 
      n = r;
   } while (r != 0);
   return m; 
}