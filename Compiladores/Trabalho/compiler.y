%{
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "src/symbolsTable.h"
#include "src/subroutines.h"
#include "src/compiler.h"
#include "src/intStack.h"

char mepaCommand[MEPA_COMMAND_SIZE];
char mepaLabel[MEPA_COMMAND_SIZE];
char subroutineLabel[LABEL_SIZE];
char leftToken[TOKEN_SIZE];

intStack_t labelStack;
intStack_t amemStack;

int numVars, labelNumber, paramsQty, actualParam;
paramItem_t* actualParamsList;
passTypes passType;
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
%type <int_val> term
%type <int_val> factor
%type <int_val> expression
%type <int_val> function_call
%type <int_val> simple_expression

%%

program:
   { generateCode(NULL, "INPP"); lexicalLevel = 0; labelNumber = 0; actualParam = -1; }
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
      removeSubroutines();

      if (blockNumVars > 0) {
         removeSymbols(blockNumVars);
         sprintf(mepaCommand, "DMEM %d", blockNumVars);
         generateCode(NULL, mepaCommand);
      }

      removeFormalParams();
   }
;

vars_declaration:  
   vars_declaration VAR declare_vars
   |
;

declare_vars: 
   declare_vars declare_var_list
   | declare_var_list
;

declare_var_list: 
   vars_list COLON var_type SEMICOLON
;

vars_list: 
   vars_list COMMA IDENT { insertSimpleVar(token, lexicalLevel, displacement++); ++numVars; }
   | IDENT { insertSimpleVar(token, lexicalLevel, displacement++); ++numVars; }
;

var_type: 
   INTEGER { setSimpleVariableType(t_integer); }
;

subroutines_declaration:
   subroutines_declaration subroutine_declaration
   |
;

subroutine_declaration:
   procedure_declariation
   | function_declaration
;

procedure_declariation:
   PROCEDURE IDENT
   {
      sprintf(mepaCommand, "DSVS R%02d", labelNumber);
      intStackPush(&labelStack, labelNumber++);
      generateCode(NULL, mepaCommand);

      sprintf(subroutineLabel, "R%02d", labelNumber);
      insertProcedure(token, ++lexicalLevel, labelNumber++);
      strncpy(leftToken, token, TOKEN_SIZE);
      passType = p_value;
      paramsQty = 0;

      sprintf(mepaCommand, "ENPR %d", lexicalLevel);
      generateCode(subroutineLabel, mepaCommand);
   }
   formal_parameters SEMICOLON block
   {
      symbolDescriber_t *symbol = symbolsTable.symbols[symbolsTable.sp];
      procedureAttributes_t * attributes = (procedureAttributes_t *)symbol->attributes;

      sprintf(mepaCommand, "RTPR %d,%d", symbol->lexicalLevel, attributes->paramsQty);
      generateCode(NULL, mepaCommand);

      sprintf(mepaLabel, "R%02d", intStackPop(&labelStack));
      generateCode(mepaLabel, "NADA");

      --lexicalLevel;
   }
;

function_declaration:
   FUNCTION IDENT
   {
      sprintf(mepaCommand, "DSVS R%02d", labelNumber);
      intStackPush(&labelStack, labelNumber++);
      generateCode(NULL, mepaCommand);

      sprintf(subroutineLabel, "R%02d", labelNumber);
      insertFunction(token, ++lexicalLevel, labelNumber++);
      strncpy(leftToken, token, TOKEN_SIZE);
      passType = p_value;
      paramsQty = 0;

      sprintf(mepaCommand, "ENPR %d", lexicalLevel);
      generateCode(subroutineLabel, mepaCommand);
   }
   formal_parameters COLON function_type SEMICOLON block
   {
      symbolDescriber_t *symbol = symbolsTable.symbols[symbolsTable.sp];
      functionAttributes_t * attributes = (functionAttributes_t *)symbol->attributes;

      sprintf(mepaCommand, "RTPR %d,%d", symbol->lexicalLevel, attributes->paramsQty);
      generateCode(NULL, mepaCommand);

      sprintf(mepaLabel, "R%02d", intStackPop(&labelStack));
      generateCode(mepaLabel, "NADA");

      --lexicalLevel;
   }
;

function_type:
   INTEGER 
   { 
      int funcPos = searchSymbol(leftToken);
      symbolDescriber_t *symbol = symbolsTable.symbols[funcPos];
      if (symbol->category == c_function) updateFunction(symbol, paramsQty, t_integer);
   }
;

formal_parameters:
   OPEN_PARENTHESES formal_parameters_section CLOSE_PARENTHESES
   {
      int procPos = searchSymbol(leftToken);
      symbolDescriber_t *symbol = symbolsTable.symbols[procPos];
      if (symbol->category == c_procedure) updateProcedure(symbol, paramsQty);
   }
   |
;

formal_parameters_section:
   formal_parameters_section SEMICOLON declare_formal_parameters
   | declare_formal_parameters
;

declare_formal_parameters:
   var_or_nothing params_list COLON param_type { passType = p_value; }
;

var_or_nothing:
   VAR { passType = p_reference; }
   |
;

params_list:
   params_list COMMA IDENT { insertFormalParam(token, lexicalLevel, passType); ++paramsQty; }
   | IDENT { insertFormalParam(token, lexicalLevel, passType); ++paramsQty; }
;

param_type:
   INTEGER { setFormalParamType(t_integer); }
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
   | first_ident
   | conditional_command
   | repetitive_command
   | read
   | write
;

first_ident:
   IDENT { strncpy(leftToken, token, TOKEN_SIZE); } ident_command
;

ident_command:
   ATTRIBUTION attribution
   | SEMICOLON proc_call_no_params
   | OPEN_PARENTHESES proc_call_with_params CLOSE_PARENTHESES SEMICOLON
;

attribution:
   expression
   {
      symbolDescriber_t *symbol = checkSymbol(leftToken, o_attribution);

      if (symbol->category == c_simple_var) {
         simpleVarAttributes_t *attributes = (simpleVarAttributes_t *)symbol->attributes;
         if (attributes->type != $1) printError("Tipos incompatives!");

         sprintf(mepaCommand, "ARMZ %d,%d", symbol->lexicalLevel, attributes->displacement);
      } else if (symbol->category == c_formal_param) {
         formalParamAttributes_t *attributes = (formalParamAttributes_t *)symbol->attributes;
         if (attributes->type != $1) printError("Tipos incompatives!");

         if (attributes->passType == p_value)
            sprintf(mepaCommand, "ARMZ %d,%d", symbol->lexicalLevel, attributes->displacement);
         else 
            sprintf(mepaCommand, "ARMI %d,%d", symbol->lexicalLevel, attributes->displacement);
      } else if (symbol->category == c_function) {
         functionAttributes_t *attributes = (functionAttributes_t *)symbol->attributes;
         if (attributes->type != $1) printError("Tipos incompatives!");

         sprintf(mepaCommand, "ARMZ %d,%d", symbol->lexicalLevel, attributes->displacement);
      }

      generateCode(NULL, mepaCommand);
   }
   SEMICOLON
;

proc_call_no_params:
   {
      symbolDescriber_t *symbol = checkSymbol(leftToken, o_procedure);
      procedureAttributes_t *attributes = (procedureAttributes_t *)symbol->attributes;

      if (attributes->paramsQty != 0) printError("Faltando parametros!");

      sprintf(mepaCommand, "CHPR R%02d,%d", attributes->label, lexicalLevel);
      generateCode(NULL, mepaCommand);
   }
;

proc_call_with_params:
   {
      symbolDescriber_t *symbol = checkSymbol(leftToken, o_procedure);
      procedureAttributes_t *attributes = (procedureAttributes_t *)symbol->attributes;
      
      actualParamsList = attributes->params;
      actualParam = 0;
   }
   expression_list
   {
      int procPos = searchSymbol(leftToken);
      symbolDescriber_t *symbol = symbolsTable.symbols[procPos];
      procedureAttributes_t *attributes = (procedureAttributes_t *)symbol->attributes;

      if (actualParam < (attributes->paramsQty - 1))
         printError("Parametros faltantes na chamada da procedimento!");
      
      sprintf(mepaCommand, "CHPR R%02d,%d", attributes->label, lexicalLevel);
      generateCode(NULL, mepaCommand);

      actualParamsList = NULL;
      actualParam = -1;
   }
;

function_call:

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
   IDENT
   {
      symbolDescriber_t *symbol = checkSymbol(token, o_read);

      if (symbol->category == c_simple_var) {
         simpleVarAttributes_t *attributes = (simpleVarAttributes_t *)symbol->attributes;

         generateCode(NULL, "LEIT");
         sprintf(mepaCommand, "ARMZ %d,%d", symbol->lexicalLevel, attributes->displacement);
      } else if (symbol->category == c_formal_param) {
         formalParamAttributes_t *attributes = (formalParamAttributes_t *)symbol->attributes;

         generateCode(NULL, "LEIT");
         if (attributes->passType == p_value)
            sprintf(mepaCommand, "ARMZ %d,%d", symbol->lexicalLevel, attributes->displacement);
         else 
            sprintf(mepaCommand, "ARMI %d,%d", symbol->lexicalLevel, attributes->displacement);
      } else if (symbol->category == c_function) {
         functionAttributes_t *attributes = (functionAttributes_t *)symbol->attributes;

         generateCode(NULL, "LEIT");
         sprintf(mepaCommand, "ARMZ %d,%d", symbol->lexicalLevel, attributes->displacement);
      }

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
   factor { generateCode(NULL, "IMPR"); }
;

expression_list:
   expression_list COMMA expression 
   {
      if (actualParamsList[actualParam++].type != $3)
         printError("Parametro de tipo incompativel!");
   }
   | expression
   {
      if (actualParamsList[actualParam++].type != $1)
         printError("Parametro de tipo incompativel!");
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
   IDENT
   {
      symbolDescriber_t *symbol = checkSymbol(token, o_read);

      if (symbol->category == c_simple_var) {
         simpleVarAttributes_t *attributes = (simpleVarAttributes_t *)symbol->attributes;

         sprintf(mepaCommand, "%s %d,%d", getLoadCommand(p_value, actualParam, actualParamsList), symbol->lexicalLevel, attributes->displacement);
         $$ = attributes->type;
      }  else if (symbol->category == c_formal_param) {
         formalParamAttributes_t *attributes = (formalParamAttributes_t *)symbol->attributes;

         sprintf(mepaCommand, "%s %d,%d", getLoadCommand(attributes->passType, actualParam, actualParamsList), symbol->lexicalLevel, attributes->displacement);
         $$ = attributes->type;
      }
      generateCode(NULL, mepaCommand);
   }
   | NUMBER
   {
      if (actualParam != -1 && actualParamsList[actualParam].passType == p_reference)
          printError("Parametro precisa ser uma variavel!");

      sprintf(mepaCommand, "CRCT %d", atoi(token));
      generateCode(NULL, mepaCommand);
      $$ = t_integer;
   }
   | function_call
   {
      $$ = $1;
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