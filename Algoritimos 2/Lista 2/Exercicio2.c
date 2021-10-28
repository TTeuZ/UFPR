#include <stdio.h>
int palindromo(int v[], int a, int b);

void main() {
    int vetor[10] = {5, 2, 1, 2, 5};
    if (palindromo(vetor, 0, 4)) printf("sim\n");
    else printf("não\n");
}

int palindromo(int v[], int a, int b) {
    if (a >= b) return 1;
    if (v[a] == v[b]) return palindromo(v,a+1,b-1);
    else return 0;
}