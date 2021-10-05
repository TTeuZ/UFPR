#include <stdio.h>
#include <stdlib.h>
int sum_positives (int max, int vetor[]);

void main (int argc, char *argv[]) {
    int vetor[100], max;
    printf ("Número de items do vetor: \n");
    scanf ("%d", &max);

    printf ("Escreva os valores do vetor: \n");
    for (int i = 0; i < max; ++i) 
        scanf("%d", &vetor[i]);

    printf("Soma: %d \n", sum_positives(max, vetor));
}

int sum_positives(int max, int vetor[]) {
    if (max == 0) return 0;
    else {
        if(vetor[max - 1] < 0) return sum_positives(max - 1, vetor);
        else return sum_positives(max - 1, vetor) + vetor[max - 1];
    }
}