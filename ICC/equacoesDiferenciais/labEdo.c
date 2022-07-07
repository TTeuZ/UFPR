#include <stdio.h>
#include <stdlib.h>

#include "edo.h"

int main () {
    edo_h *edo;
    double s_interval, f_interval, y_s_interval, y_f_interval;

    fprintf (stdout, "---------- Equações DIferenciais ----------\n");
    fprintf (stdout, "Informe as caracteristicas da Equação\n\n");
    fprintf (stdout, "Intervalor (a, b) da equação\n");
    scanf ("%f %f", s_interval, f_interval);
    fprintf (stdout, "Condições de contorno da equação\n");
    scanf ("%f %f", y_s_interval, y_f_interval);

    edo = init_edo ();

    return EXIT_SUCCESS;
}