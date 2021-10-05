#include <stdio.h>

int mdc_recursivo(int a, int b);
int mdc_iterativo(int a, int b);

void main(int argc, char *argv[]) {
    printf("Mdc recursivo: %d \n", mdc_recursivo(36, 24));
    printf("Mdc iterativo: %d \n", mdc_iterativo(36, 24));
}

int mdc_recursivo(int a, int b) {
    if (b == 0) return a;
    return mdc_recursivo(b, a % b);
}

int mdc_iterativo(int a, int b) {
    int apoio;
    while (b != 0) {
        apoio = b;
        b = a % b;
        a = apoio;
    }
    return a;
}