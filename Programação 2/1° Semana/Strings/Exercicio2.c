#include <stdio.h>
#include <string.h>

void main () {
    char string[100];
    int i = 0;

    printf("Digite a string: \n");
    scanf("%s", string);

    while (string[i] != '\0') i++;

    printf("O tamanho da string é: %d\n", i);
}

//calcula o tamanho da string sem usar o strlen