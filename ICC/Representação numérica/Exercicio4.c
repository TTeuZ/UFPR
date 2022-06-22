#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

typedef union
{
    int32_t i;
    float f;
    struct
    {   // Bitfields for exploration (32 bits = sign|exponent|mantissa)
        uint32_t mantissa : 23; // primeiros 23 bits (da direita para a esquerda)
        uint32_t exponent : 8;  // próximos 8 bits
        uint32_t sign : 1;      // proximo bit (ou seja, o bit mais a esquerda)
    } parts;
} Float_t;

void printUlps (Float_t num1, Float_t num2) {
    int ulpsDiff = abs(num1.i - num2.i);
    printf("\tULPs diff: %d\n", ulpsDiff);
}

int main () {
    Float_t num1, num2;

    printf ("Digite dois numeros reais: \n");
    scanf ("%f %f", &(num1.f), &(num2.f));

    printUlps (num1, num2);
}