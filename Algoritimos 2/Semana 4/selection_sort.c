#include <stdio.h>
int *selection_sort(int v[], int a, int b);
int min(int v[], int a, int b);
void print_array(int v[], int a, int b);

void main(int argc, char *argv[]) {
    int v[10] = {47, 2, 9, 5, 52, 10};
    selection_sort(v, 0, 5);
    print_array(v, 0, 5);
}

int *selection_sort(int v[], int a, int b) {
    if ( a >= b ) return v;
    int m = min(v, a, b);
    int x = v[a];
    v[a] = v[m];
    v[m] = x;
    return selection_sort(v, a+1, b);
}

int min(int v[], int a, int b) {
    if (a == b) return a;
    int m = min(v, a, b-1);
    if (v[b] < v[m]) m = b;
    return m;
}

void print_array(int v[], int a, int b) {
    for(int i = a; i <= b; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}