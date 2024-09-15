#ifndef __COMPILER_H__
#define __COMPILER_H__

#define TOKEN_SIZE 16
#define MEPA_COMMAND_SIZE 16

typedef enum symbols {
  symb_program,
  symb_label,
  symb_type,
  symb_array,
  symb_of,
  symb_var,
  symb_integer,
  symb_procedure,
  symb_function,
  symb_begin,
  symb_end,
  symb_goto,
  symb_if,
  symb_then,
  symb_else,
  symb_while,
  symb_do,
  symb_plus,
  symb_minus,
  symb_mult,
  symb_div,
  symb_and,
  symb_or,
  symb_not,
  symb_attribution,
  symb_semicolon,
  symb_colon,
  symb_comma,
  symb_dot,
  symb_open_parentheses,
  symb_close_parentheses,
  symb_greater,
  symb_less,
  symb_greater_equal,
  symb_less_equal,
  symb_diff,
  symb_equal,
  symb_identifier,
  symb_number,
} symbols;

// Global variables
extern symbols symbol, relation;
extern char token[TOKEN_SIZE];
extern int nl;

// Global Prototypes
void generateCode(char *, char *);
void closeMEPAFile();
void printError(char *error);

int yylex();
void yyerror(const char *s);

#endif