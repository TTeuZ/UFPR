%{
#include <stdio.h>
#include <string.h>

#include "compiler.h"
#include "compiler.tab.h"

#define PRINT(STR) printf("%s    # %s \n", STR, token);

int nl = 1;
%}

newLine [\n]
discard [\t ]+
ident [a-zA-Z][a-zA-Z0-9]*
number [0-9]+
comment "(*".*"*)"

%%

{newLine} { nl++; }
{discard}
{comment}

program { 
  symbol = symb_program;
  strncpy(token, yytext, TOKEN_SIZE);
  PRINT("program");
  return PROGRAM;
}

label {
  symbol = symb_label;
  strncpy(token, yytext, TOKEN_SIZE);
  PRINT("label");
  return LABEL;
}

type {
  symbol = symb_type;
  strncpy(token, yytext, TOKEN_SIZE);
  PRINT("type");
  return TYPE;
}

array {
  symbol = symb_array;
  strncpy(token, yytext, TOKEN_SIZE);
  PRINT("array");
  return ARRAY;
}

of {
  symbol = symb_of;
  strncpy(token, yytext, TOKEN_SIZE);
  PRINT("of");
  return OF;
}

var { 
  symbol = symb_var;
  strncpy(token, yytext, TOKEN_SIZE);
  PRINT("var");
  return VAR;
}

procedure {
  symbol = symb_procedure;
  strncpy(token, yytext, TOKEN_SIZE);
  PRINT("procedure");
  return PROCEDURE;
}

function {
  symbol = symb_function;
  strncpy(token, yytext, TOKEN_SIZE);
  PRINT("function");
  return FUNCTION;
}

begin { 
  symbol = symb_begin;
  strncpy(token, yytext, TOKEN_SIZE);
  PRINT("begin");
  return T_BEGIN;
}

end { 
  symbol = symb_end;
  strncpy(token, yytext, TOKEN_SIZE);
  PRINT("end");
  return T_END;
}

goto {
  symbol = symb_goto;
  strncpy(token, yytext, TOKEN_SIZE);
  PRINT("goto");
  return GOTO;
}

if {
  symbol = symb_if;
  strncpy(token, yytext, TOKEN_SIZE);
  PRINT("if");
  return IF;
}

then {
  symbol = symb_then;
  strncpy(token, yytext, TOKEN_SIZE);
  PRINT("then");
  return THEN;
}

else {
  symbol = symb_else;
  strncpy(token, yytext, TOKEN_SIZE);
  PRINT("else");
  return ELSE;
}

while {
  symbol = symb_while;
  strncpy(token, yytext, TOKEN_SIZE);
  PRINT("while");
  return WHILE;
}

do {
  symbol = symb_do;
  strncpy(token, yytext, TOKEN_SIZE);
  PRINT("do");
  return DO;
}

\+ {
  symbol = symb_plus;
  strncpy(token, yytext, TOKEN_SIZE);
  PRINT("plus");
  return PLUS;
}

\- {
  symbol = symb_less;
  strncpy(token, yytext, TOKEN_SIZE);
  PRINT("less");
  return LESS;
}

\* {
  symbol = symb_mult;
  strncpy(token, yytext, TOKEN_SIZE);
  PRINT("mult");
  return MULT;
}

div {
  symbol = symb_div;
  strncpy(token, yytext, TOKEN_SIZE);
  PRINT("div");
  return DIV;
}

and {
  symbol = symb_and;
  strncpy(token, yytext, TOKEN_SIZE);
  PRINT("and");
  return AND;
}

or {
  symbol = symb_or;
  strncpy(token, yytext, TOKEN_SIZE);
  PRINT("or");
  return OR; 
}

not {
  symbol = symb_not;
  strncpy(token, yytext, TOKEN_SIZE);
  PRINT("not");
  return NOT;
}

:= { 
  symbol = symb_attribution;
  strncpy(token, yytext, TOKEN_SIZE);
  PRINT("attribution");
  return ATTRIBUTION;
}

\; { 
  symbol = symb_semicolon;
  strncpy(token, yytext, TOKEN_SIZE);
  PRINT("semicolon");
  return SEMICOLON;
}

\: { 
  symbol = symb_colon;
  strncpy(token, yytext, TOKEN_SIZE);
  PRINT("colon");
  return COLON;
}

\, { 
  symbol = symb_comma;
  strncpy(token, yytext, TOKEN_SIZE);
  PRINT("comma");
  return COMMA;
}

\. { 
  symbol = symb_dot;
  strncpy(token, yytext, TOKEN_SIZE);
  PRINT("dot");
  return DOT;
}

\( { 
  symbol = symb_open_parentheses;
  strncpy(token, yytext, TOKEN_SIZE);
  PRINT("open_parentheses");
  return OPEN_PARENTHESES;
}

\) { 
  symbol = symb_close_parentheses;
  strncpy(token, yytext, TOKEN_SIZE);
  PRINT("close_parentheses");
  return CLOSE_PARENTHESES;
}

{ident} { 
  symbol = symb_identifier;
  strncpy(token, yytext, TOKEN_SIZE);
  PRINT("ident");
  return IDENT;
}

%%