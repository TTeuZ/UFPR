#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "coefficients.h"

// coeficientes da primeira equação diferencial
double p1 (double x) { return 0.0; }
double q1 (double x) { return 0.0; }
double r1 (double x) { return (6 * x) - (0.5 * pow (x, 2)); }

// coeficientes da segunda equação diferencial
double p2 (double x) { return 0.0; }
double q2 (double x) { return 1.0; }
double r2 (double x) { return 0.0; }

// coeficientes da terceira equação diferencial
double p3 (double x) { return (x + 1); }
double q3 (double x) { return 2.0; }
double r3 (double x) { return (1 - pow (x, 2)) * (exp (-x)); }