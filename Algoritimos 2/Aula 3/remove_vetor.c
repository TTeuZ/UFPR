#include <stdio.h>
int remove_r(int k, int n, int v[]);
int remove_2(int position, int start, int end, int vetor[]);

void main (int argc, char *argv[]) {
    int v[100] = {10, 23, 14, 34};
    // printf("removendo o elemento: %d\n", remove_r(2, 3, v));
    printf("removendo o elemento: %d\n", remove_2(2, 0, 3, v));
}

int remove_r(int k, int n, int v[]) {
   int x = v[k];
   if (k < n-1) {
      int y = remove_r(k+1, n, v); 
      v[k] = y;
   }
   return x;
}

int remove_2(int position, int start, int end, int vetor[]) {
    int number = vetor[position];
    if (position < end-1) {
        int next_number = remove_2(position+1, start, end, vetor);
        vetor[position] = next_number;
    } else {
        end -= end;
    }
    return number;
}