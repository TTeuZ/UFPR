%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "src/compiler.h"
#include "src/symbolsTable.h"
#include "src/intStack.h"

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
         char amem[MEPA_COMMAND_SIZE];
         sprintf(amem, "AMEM %d", numVars);
         generateCode(NULL, amem);
      }

      intStackPush(&amemStack, numVars);
   }
   compost_command
   { // DMEM
      int blockNumVars = intStackPop(&amemStack);

      if (blockNumVars > 0) {
         char dmem[MEPA_COMMAND_SIZE];
         sprintf(dmem, "DMEM %d", blockNumVars);
         generateCode(NULL, dmem);
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