#include <stdio.h>
#include <stdlib.h>
#include "bicycle.h"

void clean_bicycle (bicycle_f *bicycle) {
    int count;
    for (count = 0; count < bicycle->logs_qtd; count++) 
        free (bicycle->logs[count]);
    free (bicycle);
}