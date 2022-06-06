#include <stdio.h>
#include <string.h>

void main() {
    char teste[100] = "!str@#ing!de!!tes#@te";
    int stringSize = strlen(teste);
    int i = 0;
    while (i < stringSize) {
        if (!(teste[i] >= 'a' && teste[i] <= 'z') && !(teste[i] >= 'A' && teste[i] <= 'Z') && !(teste[i] >= '0' && teste[i] <= '9')) {
            for (int count = stringSize; count >= i; count--) {
                teste[count+1] = teste[count];
            }
            stringSize += 2;
            // teste[i-2] = '[';
            // teste[i-1] = teste[i];
            // teste[i] = ']';
        } else i++;
    }

    printf("String nova: %s\n", teste);
}

// Colocar entre colchetes ([ ]) os caracteres de uma string que não sejam letras, números ou espaço; as alterações devem ser feitas na própria string, sem usar string auxiliar