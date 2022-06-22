#include <stdio.h>
#include <stdint.h>
#include <float.h>
#include <math.h>
typedef union {
    int32_t i;
    float f;
    struct { // Bitfields for exploration. Do not use in production code.
        uint32_t mantissa : 23;
        uint32_t exponent : 8;
        uint32_t sign : 1;
    } parts;
} Float_t;

void printFloat_t( Float_t num ) {
    printf("f:%1.9e, ix:0x%08X, s:%d, e:%d, mx:0x%06X\n",
    num.f, num.i,
    num.parts.sign, num.parts.exponent, num.parts.mantissa);
}
int main() {
    Float_t num;

    scanf ("%f", &(num.f));
    printFloat_t(num);
    printf("\n");

    printf("\nEpsilon: %1.15f\n", FLT_EPSILON);
}