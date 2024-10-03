%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "src/compiler.h"
#include "src/symbolsTable.h"
#include "src/intStack.h"

char mepaCommand[MEPA_COMMAND_SIZE];
char mepaLabel[MEPA_COMMAND_SIZE];
char subroutineLabel[LABEL_SIZE];

intStack_t amemStack;
intStack_t labelStack;

int numVars, labelNumber;
%}

%token ATTRIBUTION PLUS MINUS MULT DIV AND OR NOT
%token OPEN_PARENTHESES CLOSE_PARENTHESES
%token GREATER LESS GREATER_EQUAL LESS_EQUAL DIFF EQUAL
%token SEMICOLON COLON COMMA DOT IDENT NUMBER
%token GOTO IF THEN ELSE WHILE DO
%token LABEL TYPE ARRAY OF VAR INTEGER
%token PROGRAM T_BEGIN T_END
%token PROCEDURE FUNCTION
%token READ WRITE

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

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
   { generateCode(NULL, "INPP"); lexicalLevel = 0; labelNumber = 0; }
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
   {
      if (numVars > 0) {
         sprintf(mepaCommand, "AMEM %d", numVars);
         generateCode(NULL, mepaCommand);
      }

      intStackPush(&amemStack, numVars);
   }
   subroutines_declaration
   compost_command
   {
      int blockNumVars = intStackPop(&amemStack);

      if (blockNumVars > 0) {
         removeSymbols(blockNumVars);
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
   list_var_id COLON type SEMICOLON
;

list_var_id: 
   list_var_id COMMA IDENT { insertSimpleVar(token, lexicalLevel, displacement++); ++numVars; }
   | IDENT { insertSimpleVar(token, lexicalLevel, displacement++); ++numVars; }
;

type: 
   INTEGER { setSimpleVariableType(t_integer); }
;

subroutines_declaration:
   subroutine_declaration
   |
;

subroutine_declaration
   procedure_declariation
;

procedure_declariation:
   PROCEDURE IDENT
   {
      sprintf(mepaCommand, "DSVF R%02d", labelNumber);
      intStackPush(&labelStack, labelNumber++);
      generateCode(NULL, mepaCommand);

      sprintf(subroutineLabel, "R%02d", labelNumber++);
      insertProcedure(token, ++lexicalLevel, subroutineLabel);

      sprintf(mepaCommand, "ENPR %d", lexicalLevel);
      generateCode(subroutineLabel, mepaCommand);
   }
   formal_parameters_or_empty SEMICOLON block
   {


      // TODO: Remocao das subrotinas com niveLexico k + 2
      // Retornos de funcao
      // outros tratamentos
   }
;

formal_parameters_or_empty:
   |
;

compost_command:
   T_BEGIN commands_or_nothing T_END semicolon_or_nothing
;

commands_or_nothing:
   commands
   |
;

semicolon_or_nothing:
   SEMICOLON
   |
;

commands:
   commands unlabeled_command
   | unlabeled_command
;

unlabeled_command:
   compost_command
   | attribution
   | conditional_command
   | repetitive_command
   | read
   | write
;

attribution:
   variable ATTRIBUTION expression
   {
      symbolDescriber_t *symbol = symbolsTable.symbols[$1];
      simpleVarAttributes_t *attributes = (simpleVarAttributes_t *)symbol->attributes;

      if (attributes->type != $3)
         printError("Tipos incompatives!");

      sprintf(mepaCommand, "ARMZ %d,%d", symbol->lexicalLevel, attributes->displacement);
      generateCode(NULL, mepaCommand);
   }
   SEMICOLON
;

conditional_command:
   if_then condition_else
   {
      sprintf(mepaLabel, "R%02d", intStackPop(&labelStack));
      generateCode(mepaLabel, "NADA");
   }
;

if_then:
   IF expression 
   {
      sprintf(mepaCommand, "DSVF R%02d", labelNumber);
      intStackPush(&labelStack, labelNumber++);
      generateCode(NULL, mepaCommand);
   }
   THEN unlabeled_command
   {
      sprintf(mepaCommand, "DSVS R%02d", labelNumber);
      generateCode(NULL, mepaCommand);

      int elseLabel = intStackPop(&labelStack);
      sprintf(mepaLabel, "R%02d", elseLabel);
      generateCode(mepaLabel, "NADA");

      intStackPush(&labelStack, labelNumber++);
   }
;

condition_else:
   ELSE unlabeled_command
   | %prec LOWER_THAN_ELSE
;

repetitive_command:
   WHILE 
   {
      sprintf(mepaLabel, "R%02d", labelNumber);
      intStackPush(&labelStack, labelNumber++);
      generateCode(mepaLabel, "NADA");
   }
   expression
   {
      sprintf(mepaCommand, "DSVF R%02d", labelNumber);
      intStackPush(&labelStack, labelNumber++);
      generateCode(NULL, mepaCommand);
   }
   DO unlabeled_command
   {
      int exitLabel = intStackPop(&labelStack);
      sprintf(mepaLabel, "R%02d", exitLabel);
      sprintf(mepaCommand, "DSVS R%02d", intStackPop(&labelStack));

      generateCode(NULL, mepaCommand);
      generateCode(mepaLabel, "NADA");
   }
;

read:
   READ OPEN_PARENTHESES read_items CLOSE_PARENTHESES SEMICOLON
;

read_items:
   read_items COMMA read_item 
   | read_item
;

read_item:
   variable
   {
      symbolDescriber_t *symbol = symbolsTable.symbols[$1];
      simpleVarAttributes_t *attributes = (simpleVarAttributes_t *)symbol->attributes;

      generateCode(NULL, "LEIT");
      sprintf(mepaCommand, "ARMZ %d,%d", symbol->lexicalLevel, attributes->displacement);
      generateCode(NULL, mepaCommand);
   }
;

write:
   WRITE OPEN_PARENTHESES write_values CLOSE_PARENTHESES SEMICOLON
;

write_values:
   write_values COMMA write_value
   | write_value 
;

write_value:
   variable
   {
      symbolDescriber_t *symbol = symbolsTable.symbols[$1];
      simpleVarAttributes_t *attributes = (simpleVarAttributes_t *)symbol->attributes;

      sprintf(mepaCommand, "CRVL %d,%d", symbol->lexicalLevel, attributes->displacement);
      generateCode(NULL, mepaCommand);
      generateCode(NULL, "IMPR");
   }
   | NUMBER
   {
      sprintf(mepaCommand, "CRCT %d", atoi(token));
      generateCode(NULL, mepaCommand);
      generateCode(NULL, "IMPR");
   }
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
   term mult_div_and factor
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
   initIntStack(&labelStack);

   yyparse();

   cleanSymbolsTable();
   closeMEPAFile();
   fclose(fp);

   return 0;
}