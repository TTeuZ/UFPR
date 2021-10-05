#include <stdio.h>
int fatorial (int x);
int fatorial_descendente(int n, int k);

void main (int argc, char *argv[]) {
    int n, k;
    printf("Digite o valor de n: \n");
    scanf("%d", &n);
    printf("Digite o valor de k: \n");
    scanf("%d", &k);
    printf("O fatorial descendente é: %d \n", fatorial_descendente(n, k));
}

int fatorial (int x) {
    if (x == 0) return 1;
    return x * fatorial(x - 1);
}

int fatorial_descendente(int n, int k) {
    return fatorial(n)/fatorial(n - k);
}