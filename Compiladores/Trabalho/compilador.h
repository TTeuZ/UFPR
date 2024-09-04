#define TAM_TOKEN 16

typedef enum simbolos {
  simb_program,
  simb_var,
  simb_begin,
  simb_end,
  simb_identificador,
  simb_numero,
  simb_ponto,
  simb_virgula,
  simb_ponto_e_virgula,
  simb_dois_pontos,
  simb_atribuicao,
  simb_abre_parenteses,
  simb_fecha_parenteses,
} simbolos;

// Global variables
extern simbolos simbolo, relacao;
extern char token[TAM_TOKEN];
extern int nivel_lexico;
extern int desloc;
extern int nl;

// Global Prototypes
void geraCodigo(char *, char *);
int yylex();
void yyerror(const char *s);