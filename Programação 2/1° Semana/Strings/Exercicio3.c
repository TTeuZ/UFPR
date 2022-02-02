#include <stdio.h>
#include <string.h>

void main () {
    char string[100];

    printf("Digite a string: \n");
    scanf("%s", string);

    for (int i = 0; i < strlen(string); i++) {
        if (!(string[i] >= 'a' && string[i] <= 'z'))
            string[i] += 32;
    }

    printf("O resultado da string é: %s\n", string);
}

// converte todas as letras de uma string para minusculas