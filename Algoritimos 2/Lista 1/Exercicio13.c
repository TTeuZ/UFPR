#include <stdio.h>
int sum (int v[], int a, int b);

void main (int argc, char *argv[]) {
    int v[10] = {10, 4, 6, 6};
    printf("Soma: %d \n", sum(v, 0, 3));
}

int sum(int v[], int a, int b) {
    if (a == b) return v[a];
    return v[a] + sum(v, a+1, b);
}