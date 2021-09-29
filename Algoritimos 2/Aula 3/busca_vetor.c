#include <stdio.h>
int busca(int v[], int x, int a, int b);

void main(int argc, char *argv[]) {
    int v[100] = {0, 10, 28, 34, 9, 8, 2, 98, 70, 3};
    int res = busca(v, 10, 0, 9);
    if (res == -10) printf("não \n");
    else printf("posição: %d \n", res);
}

int busca(int v[], int x, int a, int b) {
    if (a > b) return -10;
    if (x = v[b]) return b;
    return busca(v,x,a,b-1);
}