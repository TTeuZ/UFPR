#include <stdio.h>
int main() {
    float soma1=0.0f, soma2=0.0f;
    for (int i=1; i<=200; ++i)
        soma1 += 1.0f / (i*i);
    for (int i=200; i>=1; --i)
        soma2 += 1.0f / (i*i);
        
    printf("Soma1: %.10g \t Soma2: %.10g\n\n", soma1, soma2);
    return 0;
}