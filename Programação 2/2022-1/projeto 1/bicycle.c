#include <stdio.h>
#include <stdlib.h>
#include "bicycle.h"

void clean_bicycle (bicycle_f *bicycle) {
    int count;
    for (count = 0; count < bicycle->activities_qtd; count++) {
        free (bicycle->logs[count]->date);
        free (bicycle->logs[count]);
    }
    free (bicycle->name);
    free (bicycle->logs);
    free (bicycle);
}