#include <stdio.h>
#include <stdlib.h>
// f(x, y) = x*f(x, y-1)
int exponencial(int x, int y) {
    if (y == 0) return 1;
    return x * exponencial(x, y-1);
}
void main(int argc, char *argv[]) {
    int x = 2;
    int y = 4;
    printf("%d \n", exponencial(atoi(argv[1]), atoi(argv[2])));
}

// ./exp 2 4 --> 16