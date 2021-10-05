#include <stdio.h>
#include <math.h>
int progressao_geometrica(int a, int r, int n);
int power(int base, int exp);

void main(int argc, char *argv[]) {
    printf("%d \n", progressao_geometrica(1,2,3));
}

int progressao_geometrica(int a, int r, int n) {
    if (n == 0) return a;
    return a * power(r, n) + progressao_geometrica(a, r, n-1);
}

int power(int base, int exp) {
    if (exp == 0) return 1;
    return base * power(base, exp-1);
}