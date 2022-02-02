#include <stdio.h>
#include <string.h>

void main() {
    char *teste = "!string!de!!teste";
    int stringSize = strlen(teste);
    for (int i = 0; i < stringSize; i++) {
        if (!(teste[i] >= 'a' && teste[i] <= 'z') && !(teste[i] >= 'A' && teste[i] <= 'Z') && !(teste[i] >= '0' && teste[i] <= '9')) {
            for (int count = i; count < stringSize; count++) {
                teste[count] = teste[count+1];
            }
            stringSize--;
        }
    }

    // printf("String nova: %s\n", teste);
}

// Remove todos os caracteres que não são letrar ou numeros

// não deu boa essa budega, ta dando seg fault