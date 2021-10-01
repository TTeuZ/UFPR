#include <stdio.h>
int multiplicacao(int n, int m);
int wrapper_mult(int n, int m);
int multiplicacao_com_inversao(int n, int m);

void main(int argc, char *argv[]) {
    printf("%d \n", wrapper_mult(5, -3));
    printf("%d \n", wrapper_mult(10, 3));
}

// Para inverter caso o segundo parametro seja maior que o primeiro para
// mas isso acaba gerando comparações amais desnecessárias, o idela é fazer uma wrapper-function
int multiplicacao_com_inversao(int n, int m) {
    if (m > n) return multiplicacao(m, n);
    if (m == 0) return 0;
    return n + multiplicacao(n, m-1);
}

// Normalmente escrevemos a função wrapper com o nome real, pois seria a utilziada pelo usuario
int wrapper_mult(int n, int m) {
    if (m > n) return multiplicacao(m, n);
    if (m < 0) return multiplicacao(m, n); // Se o segundo numero for negativo, invertemos para poder fazer a recursividade correta
    return multiplicacao(n, m);
}

int multiplicacao(int n, int m) {
    if (m == 0) return 0;
    return n + multiplicacao(n, m-1);
}