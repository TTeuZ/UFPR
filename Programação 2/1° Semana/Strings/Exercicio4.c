#include <stdio.h>
#include <string.h>

void main () {
    char string[5][10];
    char temp[10];
    int i;

    printf("Digite as 5 string: \n");
    for (i = 0; i < 5; i++) 
        scanf("%s", string[i]);
    
    i = 0;
    while (i < 5) {
        if (strcmp (string[i], string[i+1]) > 0) {
            strcpy(temp, string[i+1]);
            strcpy(string[i+1], string[i]);
            strcpy(string[i], temp);
            i--;
        } else i++;
    }

    printf("\n");
    printf("Retornando em ordem alfabética: \n");
    for (int i = 1; i <= 5; i++) 
        printf("%s\n", string[i]);
}

// Le as linhas da entrada e retorna em ordem alfabética