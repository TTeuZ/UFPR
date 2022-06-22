// p, n, x: idem à função anterior
// px: valor do polinomio no ponto x
// dpx: valor da primeira derivada do polinomio no ponto x
void calculaPolinomioEDerivada( double *p, int n, double x, double *px, double *dpx ) {
}

// p: coeficientes de um polinomio
// n: grau do polinomio p
// x: valor inicial e resposta
// erroMax: maior erro aceitavel
int funcaoFazAlgo(double *p, int n, double *x, double erroMax ) {
    double px, dpx, erro, x_new;
    do {
        calculaPolinomioEDerivada(p, n, *x, &px, &dpx);
        if (dpx == 0.0)
            return -1;
        x_new = *x - px / dpx;
        erro = fabs( x_new - *x );
        *x = x_new;
    } while (erro > erroMax);
    return 0;
}