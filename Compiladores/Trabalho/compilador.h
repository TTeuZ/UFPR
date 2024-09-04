#define TAM_TOKEN 16

typedef enum simbolos {
  simb_program,
  simb_label,
  simb_type,
  simb_array,
  simb_of,
  simb_var,
  simb_procedure,
  simb_function,
  simb_begin,
  simb_end,
  simb_goto,
  simb_if,
  simb_then,
  simb_else,
  simb_while,
  simb_do,
  simb_mais,
  simb_menos,
  simb_mult,
  simb_div,
  simb_and,
  simb_or,
  simb_not,
  simb_atribuicao,
  simb_ponto_e_virgula,
  simb_dois_pontos,
  simb_virgula,
  simb_ponto,
  simb_abre_parenteses,
  simb_fecha_parenteses,
  simb_identificador,
  simb_numero,
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