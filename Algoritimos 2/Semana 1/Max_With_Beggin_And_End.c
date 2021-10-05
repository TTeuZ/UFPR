#include <stdio.h>
int max(int beggin, int end, int vetor[]);

void main (int argc, char *argv[]) {
    int x, y, v[100];
    printf("Digite a posição inicial do array \n");
    scanf("%d", &x);
    printf("Digite a posição final do array \n");
    scanf("%d", &y);
    printf("Digite os numeros do vetor \n");
    for (int i = x; i < y; ++i) 
        scanf("%d", &v[i]);
    printf("Maximo: %d \n", max(x, y, v));
}


//Função separa o arrai em 2 no meio, e intera cada lado separadamente
// acredito que não muda muito em questão computacinal, pois so vamos entrar
// no return de y apos passarmos por todas as casas do return de x
// o que da mais ou menos na mesma que fazer direto.
int max(int beggin, int end, int vetor[]) {
    if (beggin == end) return vetor[end];
    else {
        int middle, x, y;
        middle = (beggin + end)/2;
        x = max(beggin, middle, vetor);
        y = max(middle + 1, end, vetor);
        if (x >= y) return x;
        else return y;
    }
}