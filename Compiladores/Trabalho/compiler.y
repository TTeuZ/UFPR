%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "src/compiler.h"
#include "src/symbolsTable.h"
#include "src/stack.h"

symbolsTable_t symbolsTable;
stack_t amemStack;

int numVars;
int amemSize;
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
   { generateCode(NULL, "INPP"); 
      printf("%d\n", amemStack.sp);
   }
   PROGRAM IDENT OPEN_PARENTHESES list_idents CLOSE_PARENTHESES SEMICOLON
   block DOT 
   { generateCode(NULL, "PARA"); }
;

list_idents: 
   list_idents COMMA IDENT
   | IDENT
;

block:
   vars_declaration
   {
      if (amemSize > 0) {
         char amem[AMEM_SIZE];
         sprintf(amem, "AMEM %d", amemSize);
         generateCode(NULL, amem);
      }
   }
   compost_command
;

vars_declaration:  
   { numVars = 0; } 
   VAR declare_vars
   |
;

declare_vars: 
   declare_vars declare_var
   | declare_var
;

declare_var: 
   {}
   list_var_id COLON type
   {}
   SEMICOLON
;

list_var_id: 
   list_var_id COMMA IDENT
   {}
   | IDENT 
   {}
;

type: 
   INTEGER
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
   initStack(&amemStack);

   yyparse();

   cleanSymbolsTable();
   closeMEPAFile();
   fclose(fp);
   return 0;
}