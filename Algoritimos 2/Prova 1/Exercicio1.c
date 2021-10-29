#include <stdio.h>
int f(int v[], int w[], int a, int b);

void main() {
    int v[10] = {10, 5, 4, 2};
    int w[10] = {2, 4, 5, 10};
    if (f(v, w, 0 , 3) == 1) printf("sim\n");
    else printf("não\n");
}

int f(int v[], int w[], int a, int b) {
    if (a > b) return 1;
    if (v[a] == w[b-a]) return f(v, w, a+1, b);
    else return 0;
}