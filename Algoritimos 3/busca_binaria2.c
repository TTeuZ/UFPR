#include <stdio.h>

// retorna 1 se encoutrou o numero e 0 caso o contrario
int binarySearch (int *v, int x, int beggin, int end) {
    if (beggin > end) return beggin-1;
    int middle = (end+beggin)/2;
    if (x < v[middle]) return binarySearch(v, x, beggin, middle - 1);
    return binarySearch(v, x, middle+1, end);
}

void main() {
    int v[] = {10, 13, 38, 69, 70, 80};
    int x;

    printf("Digite o numero que deseja encontrar:\n");
    scanf("%d", &x);

    printf("retorno da busca: %d\n", binarySearch (v, x, 0, 5));
}