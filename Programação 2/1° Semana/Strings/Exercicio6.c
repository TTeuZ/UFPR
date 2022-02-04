#include <stdio.h>
#include <string.h>

void main() {
    char teste[100] = "pastaadeemoraango";
    int stringSize = strlen(teste);
    int i = 0;
    while (i < stringSize) {
        if (teste[i] == teste[i+1]) {
            for (int count = i; count < stringSize; count++) {
                teste[count] = teste[count+1];
            }
            stringSize--;
        } else i++;
    }

    printf("String nova: %s\n", teste);
}

// Remove os caracteres repetidos
