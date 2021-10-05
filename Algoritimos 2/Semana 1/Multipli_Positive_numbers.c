#include <stdio.h>
#include <stdlib.h>
int multi_positives (int max, int vetor[]);

void main (int argc, char *argv[]) {
    int vetor[100], max;
    printf ("Número de items do vetor: \n");
    scanf ("%d", &max);

    printf ("Escreva os valores do vetor: \n");
    for (int i = 0; i < max; ++i) 
        scanf("%d", &vetor[i]);

    printf("Multiplicação: %d \n", multi_positives(max, vetor));
}

int multi_positives(int max, int vetor[]) {
    if (max == 0) return 1;
    else {
        if(vetor[max - 1] < 0) return multi_positives(max - 1, vetor);
        else return multi_positives(max - 1, vetor) * vetor[max - 1];
    }
}