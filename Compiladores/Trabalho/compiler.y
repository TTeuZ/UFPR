%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "src/compiler.h"
#include "src/symbolsTable.h"
#include "src/intStack.h"

char mepaCommand[MEPA_COMMAND_SIZE];
intStack_t amemStack;
int numVars;
%}

%token ATTRIBUTION PLUS MINUS MULT DIV AND OR NOT
%token OPEN_PARENTHESES CLOSE_PARENTHESES
%token GREATER LESS GREATER_EQUAL LESS_EQUAL DIFF EQUAL
%token SEMICOLON COLON COMMA DOT IDENT NUMBER
%token GOTO IF THEN ELSE WHILE DO
%token LABEL TYPE ARRAY OF VAR INTEGER
%token PROGRAM T_BEGIN T_END
%token PROCEDURE FUNCTION

%union {
   char *str;
   int int_val;
}

%type <str> relation
%type <str> mult_div_and
%type <str> plus_minus_or
%type <str> plus_minus_empty
%type <int_val> variable
%type <int_val> expression
%type <int_val> simple_expression
%type <int_val> term
%type <int_val> factor

%%

program:
   { generateCode(NULL, "INPP"); lexicalLevel = 0; }
   PROGRAM IDENT OPEN_PARENTHESES idents_list CLOSE_PARENTHESES SEMICOLON
   block DOT 
   { generateCode(NULL, "PARA"); }
;

idents_list: 
   idents_list COMMA IDENT
   | IDENT
;

block:
   { numVars = 0; displacement = 0; } 
   vars_declaration
   { // AMEM
      if (numVars > 0) {
         sprintf(mepaCommand, "AMEM %d", numVars);
         generateCode(NULL, mepaCommand);
      }

      intStackPush(&amemStack, numVars);
   }
   compost_command
   { // DMEM
      int blockNumVars = intStackPop(&amemStack);

      if (blockNumVars > 0) {
         sprintf(mepaCommand, "DMEM %d", blockNumVars);
         generateCode(NULL, mepaCommand);
      }
   }
;

vars_declaration:  
   vars_declaration VAR declare_vars
   |
;

declare_vars: 
   declare_vars declare_var
   | declare_var
;

declare_var: 
   list_var_id COLON type
   SEMICOLON
;

list_var_id: 
   list_var_id COMMA IDENT { insertSimpleVar(token, lexicalLevel, displacement++); ++numVars; }
   | IDENT { insertSimpleVar(token, lexicalLevel, displacement++); ++numVars; }
;

type: 
   INTEGER { setSimpleVariableType(t_integer); }
;

compost_command:
   T_BEGIN commands T_END
;

commands:
   commands unlabeled_command
   | unlabeled_command
   |
;

unlabeled_command:
   attribution
;

attribution:
   variable ATTRIBUTION expression
   {
      symbolDescriber_t *symbol = symbolsTable.symbols[$1];
      simpleVarAttributes_t *attributes = (simpleVarAttributes_t *)symbol->attributes;

      if (attributes->type != $3)
         printError("Tipos incompatives!");

      sprintf(mepaCommand, "ARMZ %d, %d", symbol->lexicalLevel, attributes->displacement);
      generateCode(NULL, mepaCommand);
   }
   SEMICOLON
;

expression:
   simple_expression relation simple_expression
   {
      if ($1 != t_integer || $3 != t_integer)
         printError("Tipos incompatives!");

      sprintf(mepaCommand, "%s", $2);
      generateCode(NULL, mepaCommand);
      $$ = t_boolean;
   }
   | simple_expression { $$ = $1; }
;

relation:
   EQUAL { $$ = "CMIG"; }
   | DIFF { $$ = "CMDG"; }
   | GREATER { $$ = "CMMA"; }
   | GREATER_EQUAL { $$ = "CMAG"; }
   | LESS_EQUAL { $$ = "CMEG"; }
   | LESS { $$ = "CMME"; }
;

simple_expression:
   simple_expression plus_minus_or term
   {
      if (strcmp("DISJ", $2) == 0 && ($1 != t_boolean || $3 != t_boolean))
         printError("Tipos incompatives!");
      else if (strcmp("DISJ", $2) != 0 && ($1 != t_integer || $3 != t_integer))
         printError("Tipos incompatives!");
      else if ($1 != $3) 
         printError("Tipos incompatives!");

      sprintf(mepaCommand, "%s", $2);
      generateCode(NULL, mepaCommand);
      $$ = strcmp("DISJ", $2) != 0 ? t_integer : t_boolean;
   }
   | plus_minus_empty term
   {
      if (strcmp("NADA", $1) != 0) {
         if ($2 != t_integer)
            printError("Tipos incompatives!");
         
         if (strcmp("SUBT", $1) == 0)
            generateCode(NULL, "INVR");
      }
      $$ = $2;
   }
;

plus_minus_or:
   PLUS { $$ = "SOMA"; }
   | MINUS { $$ = "SUBT"; }
   | OR { $$ = "DISJ"; }
;

plus_minus_empty:
   PLUS { $$ = "SOMA"; }
   | MINUS { $$ = "SUBT"; }
   | { $$ = "NADA"; }
;

term:
   factor mult_div_and factor
   {
      if (strcmp("CONJ", $2) == 0 && ($1 != t_boolean || $3 != t_boolean))
         printError("Tipos incompatives!");
      else if (strcmp("CONJ", $2) != 0 && ($1 != t_integer || $3 != t_integer))
         printError("Tipos incompatives!");
      else if ($1 != $3) 
         printError("Tipos incompatives!");

      sprintf(mepaCommand, "%s", $2);
      generateCode(NULL, mepaCommand);
      $$ = strcmp("CONJ", $2) != 0 ? t_integer : t_boolean;
   }
   | factor { $$ = $1; }
;

mult_div_and:
   MULT { $$ = "MULT"; }
   | DIV { $$ = "DIVI"; }
   | AND { $$ = "CONJ"; }
;

factor:
   variable
   {
      symbolDescriber_t *symbol = symbolsTable.symbols[$1];
      simpleVarAttributes_t *attributes = (simpleVarAttributes_t *)symbol->attributes;
      sprintf(mepaCommand, "CRVL %d,%d", symbol->lexicalLevel, attributes->displacement);
      generateCode(NULL, mepaCommand);
      $$ = attributes->type;
   }
   | NUMBER
   {
      sprintf(mepaCommand, "CRCT %d", atoi(token));
      generateCode(NULL, mepaCommand);
      $$ = t_integer;
   }
   | OPEN_PARENTHESES expression CLOSE_PARENTHESES
   { 
      $$ = $2; 
   }
   | NOT factor
   { 
      if ($2 != t_boolean)
         printError("Tipo incompativel!");
      
      generateCode(NULL, "NEGA");
      $$ = t_boolean;
   }
;
// TODO: Ta certo o NOT factor e OPEN_PARENTHESES expression CLOSE_PARENTHESES

variable:
   IDENT
   {
      int varPos = searchSymbol(token);
      if (varPos == -1) printError("variavel nao declarada!");
      $$ = varPos;
   }
;

%%

int main (int argc, char** argv) {
   extern FILE* yyin;
   FILE* fp;

   if (argc < 2 || argc > 2) {
      printf("usage compiler <arq>a %d\n", argc);
      return(-1);
   }

   fp = fopen(argv[1], "r");
   if (fp == NULL) {
      printf("usage compiler <arq>b\n");
      return(-1);
   }

   yyin = fp;
   initSymbolsTable();
   initIntStack(&amemStack);

   yyparse();

   cleanSymbolsTable();
   closeMEPAFile();
   fclose(fp);

   return 0;
}