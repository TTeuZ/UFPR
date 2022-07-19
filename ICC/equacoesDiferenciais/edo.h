#ifndef __EDO_H__
#define __EDO_H__
typedef struct {
	int n; // número de pontos internos na malha
	double a, b; // intervalo
	double ya, yb; // condições contorno
	double (*p)(double), (*q)(double), (*r)(double); // ponteiros para funções
} edo_h;

/*!
	\brief Aloca o espaço em mêmoria para o EDO
	\return Ponteiro de acesso para o espaço alocado em caso de sucesso. NULL em caso de falha
*/
edo_h *aloc_edo ();

/*!
	\brief Seta os valores de intervalo e as condições de contorno da EDO
	\param edo Estrutura de dados do EDO
	\param a Valor do inicio do intervalo
	\param b Valor do fim do intervalo
	\param ya Condição de contorno do inicio do intervalo
	\param yb Condição ed contorno do fim do intervalo
*/
void set_edo_conditions (edo_h *edo, double a, double b, double ya, double yb);

/*!
	\brief Seta as funções de coeficientes do EDO
	\param edo Estrutura de dados do EDO
	\param p Função de coeficiente que multiplica o y'
	\param q Função de coeficiente que multiplica o y
	\param r Função do termo independente
*/
void set_edo_coefficients (edo_h *edo, double (*p) (double), double (*q) (double), double (*r) (double));

/*!
	\brief Seta o valor da quantidade de pontos internos da malha para solução do EDO
	\param edo Estrutura de dados do EDO
	\param n numero de pontos internos da malha
*/
void set_edo_mesh (edo_h *edo, int n);
#endif