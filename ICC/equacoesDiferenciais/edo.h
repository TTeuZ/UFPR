typedef struct {
	double *d, *di, *ds, *b;
	int n;
} sl_tridiag;

// Equação Diferencial Ordinária para MDF
typedef struct {
	int n; // número de pontos internos na malha
	double s_interval, f_interval; // intervalo
	double y_s_interval, y_f_interval; // condições contorno
	double (* p)(double), (* q)(double), (* r)(double); // ponteiros para funções
} edo_h;

sl_tridiag *aloc_sislin ();

/*
* aloca espaço em memoria para a estrutura da equação
* inicializa os valores do edo
*/
edo_h *init_edo (double s_interval, double f_interval, double y_s_interval, double y_f_interval, int n);