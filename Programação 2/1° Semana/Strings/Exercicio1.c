#include <stdio.h>
#include <string.h>

void main() {
    char string[100];

    printf("Digite a string: \n");
    // scanf("%s", string);
    fgets(string, 100, stdin);

    for (int i = strlen(string); i >= 0; i--) {
        putchar(string[i]);
    }
    printf("\n");
}

// recebe uma string de entrada e printa ela ao contrario