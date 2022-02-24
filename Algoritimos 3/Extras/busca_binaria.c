#include <stdio.h>

// retorna 1 se encoutrou o numero e 0 caso o contrario
int binarySearch (int *v, int x, int beggin, int end) {
    if (beggin > end) return 0;
    int middle = (end+beggin)/2;
    if (v[middle] == x) return 1;
    if (v[middle] > x) return binarySearch(v, x, beggin, middle - 1);
    return binarySearch(v, x, middle + 1, end);
}

void main() {
    int v[] = {10, 13, 38, 69, 70, 80};
    int x;

    printf("Digite o numero que deseja encontrar:\n");
    scanf("%d", &x);

    if (binarySearch (v, x, 0, 5))
        printf("O numero foi encontrado =D\n");
    else 
        printf("O numero não foi encontrado =c\n");
}