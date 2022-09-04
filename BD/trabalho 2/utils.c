#include "utils.h"

int includes (int number, int size, int *array) {
    int count;

    for (count = 0; count < size; count++) {
        if (number == array[count])
            return true;
    }
    return false;
}