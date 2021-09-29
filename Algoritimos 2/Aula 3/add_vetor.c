#include <stdio.h>
void add_v(int position, int number, int end, int v[]);

void main (int argc, char *argv[]) {
    int v[100] = {10, 23, 14, 34};
    add_v(2, 10, 4, v);
    for (int i = 0; i <= 4; i++) {
        printf("- %d -", v[i]);
    }
}

void add_v (int position, int number, int end, int v[]) {
   if (position == end)  v[end] = number;
   else {
      v[end] = v[end-1];
      add_v (position, number, end - 1, v);
   }
}