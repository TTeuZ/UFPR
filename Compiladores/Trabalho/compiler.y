%{
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "src/symbolsTable.h"
#include "src/symbolsStack.h"
#include "src/subroutines.h"
#include "src/compiler.h"
#include "src/intStack.h"

char mepaCommand[MEPA_COMMAND_SIZE];
char mepaLabel[MEPA_COMMAND_SIZE];

char subroutineToken[TOKEN_SIZE];
char factorToken[TOKEN_SIZE];
char leftToken[TOKEN_SIZE];

symbolsStack_t subroutineStack;
intStack_t actualParamsStack;
intStack_t labelStack;
intStack_t amemStack;

int lexicalLevel, displacement, numVars, labelNumber, paramsQty, actualParam, alreadyDeclared, itsFoward;
symbolDescriber_t* actualSubroutine;
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
%token FORWARD

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
%type <int_val> factor_ident
%type <int_val> commun_factor
%type <int_val> simple_expression
%type <int_val> factor_ident_command
%type <int_val> func_call_with_params

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
   { numVars = 0; displacement = 0;  alreadyDeclared = 0; } 
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
      removeSubroutines(lexicalLevel);

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
   declare_vars declare_var_list SEMICOLON 
   | declare_var_list SEMICOLON
;

declare_var_list: 
   vars_list COLON var_type
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
   procedure_declariation SEMICOLON
   | function_declaration SEMICOLON
;

procedure_declariation:
   procedure_forward
   | procedure_definition
;

procedure_initiation:
   PROCEDURE IDENT
   {
      alreadyDeclared = searchSymbol(token) != -1;

      ++lexicalLevel;
      if (!alreadyDeclared) {
         sprintf(mepaCommand, "DSVS R%02d", labelNumber);
         intStackPush(&labelStack, labelNumber++);
         generateCode(NULL, mepaCommand);

         sprintf(mepaLabel, "R%02d", labelNumber);
         insertProcedure(token, lexicalLevel, labelNumber++);

         sprintf(mepaCommand, "ENPR %d", lexicalLevel);
         generateCode(mepaLabel, mepaCommand);

         strncpy(subroutineToken, token, TOKEN_SIZE);
         passType = p_value;
         paramsQty = 0;
      }
   }
   formal_parameters SEMICOLON
;

procedure_forward:
   procedure_initiation FORWARD { --lexicalLevel; }
;

procedure_definition:
   procedure_initiation 
   block
   {
      symbolDescriber_t *symbol = symbolsTable.symbols[symbolsTable.sp];
      procedureAttributes_t * attributes = (procedureAttributes_t *)symbol->attributes;

      sprintf(mepaCommand, "RTPR %d, %d", symbol->lexicalLevel, attributes->paramsQty);
      generateCode(NULL, mepaCommand);

      sprintf(mepaLabel, "R%02d", intStackPop(&labelStack));
      generateCode(mepaLabel, "NADA");
      --lexicalLevel;
   }
;

function_declaration:
   function_forward
   | function_definition
;

function_initiation:
   FUNCTION IDENT
   {
      alreadyDeclared = searchSymbol(token) != -1;

      ++lexicalLevel;
      if (!alreadyDeclared) {
         sprintf(mepaCommand, "DSVS R%02d", labelNumber);
         intStackPush(&labelStack, labelNumber++);
         generateCode(NULL, mepaCommand);

         sprintf(mepaLabel, "R%02d", labelNumber);
         insertFunction(token, lexicalLevel, labelNumber++);

         sprintf(mepaCommand, "ENPR %d", lexicalLevel);
         generateCode(mepaLabel, mepaCommand);

         strncpy(subroutineToken, token, TOKEN_SIZE);
         passType = p_value;
         paramsQty = 0;
      }
   }
   formal_parameters COLON function_type SEMICOLON
;

function_type:
   INTEGER 
   { 
      if (!alreadyDeclared) {
         int funcPos = searchSymbol(subroutineToken);
         symbolDescriber_t *symbol = symbolsTable.symbols[funcPos];
         if (symbol->category == c_function) updateFunction(symbol, paramsQty, t_integer);
      }
   }
;

function_forward:
   function_initiation FORWARD { --lexicalLevel; }
;

function_definition:
   function_initiation 
   block
   {
      symbolDescriber_t *symbol = symbolsTable.symbols[symbolsTable.sp];
      functionAttributes_t * attributes = (functionAttributes_t *)symbol->attributes;

      sprintf(mepaCommand, "RTPR %d, %d", symbol->lexicalLevel, attributes->paramsQty);
      generateCode(NULL, mepaCommand);

      sprintf(mepaLabel, "R%02d", intStackPop(&labelStack));
      generateCode(mepaLabel, "NADA");
      --lexicalLevel;
   }
;

formal_parameters:
   OPEN_PARENTHESES formal_parameters_section CLOSE_PARENTHESES
   {
      if (!alreadyDeclared) {
         int procPos = searchSymbol(subroutineToken);
         symbolDescriber_t *symbol = symbolsTable.symbols[procPos];
         if (symbol->category == c_procedure) updateProcedure(symbol, paramsQty);
      }
   }
   | 
;

formal_parameters_section:
   formal_parameters_section SEMICOLON declare_formal_parameters
   | declare_formal_parameters
   | 
;

declare_formal_parameters:
   var_or_nothing params_list COLON param_type { passType = p_value; }
;

var_or_nothing:
   VAR { passType = p_reference; }
   |
;

params_list:
   params_list COMMA IDENT 
   { 
      if (!alreadyDeclared) {
         insertFormalParam(token, lexicalLevel, passType); 
         ++paramsQty; 
      }
   }
   | IDENT 
   { 
      if (!alreadyDeclared) {
         insertFormalParam(token, lexicalLevel, passType); 
         ++paramsQty; 
      }
   }
;

param_type:
   INTEGER { setFormalParamType(t_integer); }
;

compost_command:
   T_BEGIN commands T_END
;

commands:
   commands SEMICOLON unlabeled_command
   | unlabeled_command
;

unlabeled_command:
   compost_command
   | first_ident
   | conditional_command
   | repetitive_command
   | read
   | write
   |
;

first_ident:
   IDENT { strncpy(leftToken, token, TOKEN_SIZE); } ident_command
;

ident_command:
   ATTRIBUTION attribution
   | proc_call_no_params
   | OPEN_PARENTHESES proc_call_with_params CLOSE_PARENTHESES
;

attribution:
   expression
   {
      symbolDescriber_t *symbol = checkSymbol(leftToken, o_attribution);

      if (symbol->category == c_simple_var) {
         simpleVarAttributes_t *attributes = (simpleVarAttributes_t *)symbol->attributes;
         if (attributes->type != $1) printError("Tipos incompatives!");

         sprintf(mepaCommand, "ARMZ %d, %d", symbol->lexicalLevel, attributes->displacement);
      } else if (symbol->category == c_formal_param) {
         formalParamAttributes_t *attributes = (formalParamAttributes_t *)symbol->attributes;
         if (attributes->type != $1) printError("Tipos incompatives!");

         if (attributes->passType == p_value)
            sprintf(mepaCommand, "ARMZ %d, %d", symbol->lexicalLevel, attributes->displacement);
         else 
            sprintf(mepaCommand, "ARMI %d, %d", symbol->lexicalLevel, attributes->displacement);
      } else if (symbol->category == c_function) {
         functionAttributes_t *attributes = (functionAttributes_t *)symbol->attributes;

         if (attributes->type != $1) printError("Tipos incompatives!");

         sprintf(mepaCommand, "ARMZ %d, %d", symbol->lexicalLevel, attributes->displacement);
      }

      generateCode(NULL, mepaCommand);
   }
;

proc_call_no_params:
   {
      symbolDescriber_t *symbol = checkSymbol(leftToken, o_procedure);
      procedureAttributes_t *attributes = (procedureAttributes_t *)symbol->attributes;

      if (attributes->paramsQty != 0) printError("Faltando parametros!");

      sprintf(mepaCommand, "CHPR R%02d, %d", attributes->label, lexicalLevel);
      generateCode(NULL, mepaCommand);
   }
;

proc_call_with_params:
   {
      symbolDescriber_t *symbol = checkSymbol(leftToken, o_procedure);
      procedureAttributes_t *attributes = (procedureAttributes_t *)symbol->attributes;
      
      if (actualSubroutine != NULL) {
         symbolsStackPush(&subroutineStack, actualSubroutine);
         intStackPush(&actualParamsStack, actualParam);
      }

      actualSubroutine = symbol;
      actualParam = 0;
   }
   expression_list
   {
      procedureAttributes_t *attributes = (procedureAttributes_t *)actualSubroutine->attributes;

      if (actualParam < (attributes->paramsQty - 1))
         printError("Quantidade invalida de parametros!");
      
      sprintf(mepaCommand, "CHPR R%02d, %d", attributes->label, lexicalLevel);
      generateCode(NULL, mepaCommand);

      actualSubroutine = symbolsStackPop(&subroutineStack);
      actualParam = intStackPop(&actualParamsStack);
   }
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
      if ($2 == t_integer)
         printError("Tipos incompatives!");

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
   READ OPEN_PARENTHESES read_items CLOSE_PARENTHESES
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
         sprintf(mepaCommand, "ARMZ %d, %d", symbol->lexicalLevel, attributes->displacement);
      } else if (symbol->category == c_formal_param) {
         formalParamAttributes_t *attributes = (formalParamAttributes_t *)symbol->attributes;

         generateCode(NULL, "LEIT");
         if (attributes->passType == p_value)
            sprintf(mepaCommand, "ARMZ %d, %d", symbol->lexicalLevel, attributes->displacement);
         else 
            sprintf(mepaCommand, "ARMI %d, %d", symbol->lexicalLevel, attributes->displacement);
      } else if (symbol->category == c_function) {
         if (strcmp(subroutineToken, token) != 0) printError("Assinalando retorno para funcao incorreta!");
         functionAttributes_t *attributes = (functionAttributes_t *)symbol->attributes;

         generateCode(NULL, "LEIT");
         sprintf(mepaCommand, "ARMZ %d, %d", symbol->lexicalLevel, attributes->displacement);
      }

      generateCode(NULL, mepaCommand);
   }
;

write:
   WRITE OPEN_PARENTHESES write_values CLOSE_PARENTHESES
;

write_values:
   write_values COMMA write_value
   | write_value 
;

write_value:
   factor { generateCode(NULL, "IMPR"); }
;

expression_list:
   expression_list COMMA expression { checkParamType($3, actualParam++, actualSubroutine); }
   | expression { checkParamType($1, actualParam++, actualSubroutine); }
   |
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
   factor_ident
   {
      $$ = $1;
   }
   | NUMBER
   {
      if (actualSubroutine != NULL && actualSubroutine->category == c_procedure) {
         procedureAttributes_t *attributes = (procedureAttributes_t *)actualSubroutine->attributes;
         if (attributes->params[actualParam].passType == p_reference) printError("Parametro precisa ser uma variavel!");
      } else if (actualSubroutine != NULL && actualSubroutine->category == c_function) {
         functionAttributes_t *attributes = (functionAttributes_t *)actualSubroutine->attributes;
         if (attributes->params[actualParam].passType == p_reference) printError("Parametro precisa ser uma variavel!");
      }

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

factor_ident:
   IDENT { strncpy(factorToken, token, TOKEN_SIZE); } factor_ident_command { $$ = $3; }
;

factor_ident_command:
   OPEN_PARENTHESES func_call_with_params CLOSE_PARENTHESES { $$ = $2; }
   | commun_factor { $$ = $1; }
;

commun_factor:
   {
      symbolDescriber_t *symbol = checkSymbol(factorToken, o_read);

      if (symbol->category == c_simple_var) {
         simpleVarAttributes_t *attributes = (simpleVarAttributes_t *)symbol->attributes;

         sprintf(mepaCommand, "%s %d, %d", getLoadCommand(p_value, actualParam, actualSubroutine), symbol->lexicalLevel, attributes->displacement);
         $$ = attributes->type;
      }  else if (symbol->category == c_formal_param) {
         formalParamAttributes_t *attributes = (formalParamAttributes_t *)symbol->attributes;

         sprintf(mepaCommand, "%s %d, %d", getLoadCommand(attributes->passType, actualParam, actualSubroutine), symbol->lexicalLevel, attributes->displacement);
         $$ = attributes->type;
      } else if (symbol->category == c_function) {
         functionAttributes_t *attributes = (functionAttributes_t *)symbol->attributes;
         generateCode(NULL, "AMEM 1");

         sprintf(mepaCommand, "CHPR R%02d, %d", attributes->label, lexicalLevel);
         $$ = attributes->type;
      }
      generateCode(NULL, mepaCommand);
   }
;

func_call_with_params:
   {
      symbolDescriber_t *symbol = checkSymbol(factorToken, o_function);
      functionAttributes_t *attributes = (functionAttributes_t *)symbol->attributes;
      
      if (actualSubroutine != NULL) {
         symbolsStackPush(&subroutineStack, actualSubroutine);
         intStackPush(&actualParamsStack, actualParam);
      }

      generateCode(NULL, "AMEM 1");
      actualSubroutine = symbol;
      actualParam = 0;
   }
   expression_list
   {
      functionAttributes_t *attributes = (functionAttributes_t *)actualSubroutine->attributes;

      if (actualParam < (attributes->paramsQty - 1))
         printError("Quantidade invalida de parametros!");
      
      sprintf(mepaCommand, "CHPR R%02d, %d", attributes->label, lexicalLevel);
      generateCode(NULL, mepaCommand);
      $$ = attributes->type;

      actualSubroutine = symbolsStackPop(&subroutineStack);
      actualParam = intStackPop(&actualParamsStack);
   }

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
   initIntStack(&actualParamsStack);
   initSymbolsStack(&subroutineStack);

   yyparse();

   cleanSymbolsTable();
   closeMEPAFile();
   fclose(fp);

   return 0;
}