// //Organização por inserção;

#include <stdio.h>
int *insection_sort(int v[], int a, int b);
int *insert(int v[], int a, int b);
int find(int x,int v[], int a, int b);
void print_array(int v[], int a, int b);

void main(int argc, char *argv[]) {
    int v[10] = {99, 35, 27, 22, 9, 5};
    insection_sort(v, 0, 5);
    print_array(v, 0, 5);
}

int *insection_sort(int v[], int a, int b) {
    if (a >= b) return v;
    insection_sort(v, a, b-1);
    return insert(v, a, b);
}

int *insert(int v[], int a, int b) {
    int p = find(v[b], v, a, b-1);
    int i = b;
    while (i > p + 1) {
        int x = v[i];
        v[i] = v[i-1];
        v[i-1] = x;
        i = i - 1;
    }
    return v;
}
int find(int x,int v[], int a, int b) {
    if (a > b) return a-1;
    if (x >= v[b]) return b;
    return find(x, v, a, b-1);
}

void print_array(int v[], int a, int b) {
    for(int i = a; i <= b; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}