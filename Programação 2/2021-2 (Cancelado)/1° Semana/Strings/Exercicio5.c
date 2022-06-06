#include <stdio.h>
#include <string.h>

void main() {
    char teste[100] = "!str@#ing!de!!tes#@te";
    int stringSize = strlen(teste);
    int i = 0;
    while (i < stringSize) {
        if (!(teste[i] >= 'a' && teste[i] <= 'z') && !(teste[i] >= 'A' && teste[i] <= 'Z') && !(teste[i] >= '0' && teste[i] <= '9')) {
            for (int count = i; count < stringSize; count++) {
                teste[count] = teste[count+1];
            }
            stringSize--;
        } else i++;
    }

    printf("String nova: %s\n", teste);
}

// Remove todos os caracteres que não são letrar ou numeros