#include "utils.h"

int fat (int number) {
    int fatorial, n;
    n = number;
    fatorial = 1;

    while (n > 1) {
        fatorial = fatorial * n;
        n--;
    }
    return fatorial;
}

int includes (int number, int size, int *array) {
    int count;

    for (count = 0; count < size; count++) {
        if (number == array[count])
            return true;
    }
    return false;
}