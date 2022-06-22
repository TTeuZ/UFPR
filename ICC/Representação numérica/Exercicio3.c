#include <stdio.h>
#include <float.h>


float get_epsilon (float num) {
    return num * FLT_EPSILON;
}

int main () {
    float num, epsilon;

    printf("Informe um numero real: \n");
    scanf ("%f", &num);

    epsilon = get_epsilon (num);
    printf ("o epslon do numero é %0.9f\n", epsilon);
}