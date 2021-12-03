#include <stdio.h>
void imprime_vetor(int set[], int v[], int a) {
    for(int i = 0; i <= a; i++) {
        if (v[i])
            printf("%d ", set[i]);
    }
    printf("\n");
}

int eh_menor (int set[], int v[], int n, int b) {
    int count, soma = 0;

    for(count = 0; count <= n; count++) {
        if (v[count]) {
            soma = soma + set[count];
        }
    }
    if (soma >= b) return 0;
    return 1;
}
// algoritmo backtracking
void bt(int set[], int v[], int n, int i, int b) {
    if (i == n) {
        imprime_vetor(set, v, n);
        return;
    }
    if (eh_menor (set, v, i, b)) {
        v[i] = 0;
        bt(set, v, n, i + 1, b);
        v[i] = 1;
        bt(set, v, n, i + 1, b);
    }
}
// imprime_todos_subconjuntos
void subconjuntos(int set[], int n) {
    int v[n];
    bt(set,v,n,0,40);
}
// exemplo de uso
int main() {
    int set[] = {23, 10, 20, 11, 12, 6, 7, 2, 3, 9};
    int n = 10;
    subconjuntos(set, n);
}