#include <stdio.h>
int *merge_sort(int v[], int a, int b);
int *merge(int v[], int a, int m, int b);
void print_array(int v[], int a, int b);

void main(int argc, char *argv[]) {
    int v[10] = {7, 58, 31, 92, 3, 10};
    merge_sort(v, 0, 5);
    print_array(v, 0, 5);
}

int *merge_sort(int v[], int a, int b) {
    if (a >= b) return v;
    int m = (a+b)/2;
    merge_sort(v, a, m);
    merge_sort(v, m+1, b);
    return merge(v, a, m, b);
}

int *merge(int v[], int a, int m, int b) {
    if (a >= b) return v;
    int u[100];
    int i = a;
    int j = m + 1;
    for (int k = a; k <= b; k++) {
        if (j > b || (i <= m && v[i] <= v[j])) {
            u[k] = v[i];
            i += 1;
        } else {
            u[k] = v[j];
            j += 1;
        }
    };
    for (int p = 0; p <= b; p++) {
        v[p] = u[p];
    };
    return v;
}

void print_array(int v[], int a, int b) {
    for(int i = a; i <= b; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}