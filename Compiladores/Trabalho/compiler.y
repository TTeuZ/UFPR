%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "src/compiler.h"
#include "src/symbolsTable.h"

int numVars;
%}

%token ATTRIBUTION PLUS LESS MULT DIV AND OR NOT
%token OPEN_PARENTHESES CLOSE_PARENTHESES
%token SEMICOLON COLON COMMA DOT IDENT
%token GOTO IF THEN ELSE WHILE DO
%token LABEL TYPE ARRAY OF VAR
%token PROGRAM T_BEGIN T_END
%token PROCEDURE FUNCTION

%%

program:
   { generateCode(NULL, "INPP"); }
   PROGRAM IDENT OPEN_PARENTHESES list_idents CLOSE_PARENTHESES SEMICOLON
   block DOT 
   { generateCode(NULL, "PARA"); }
;

list_idents: 
   list_idents COMMA IDENT
   | IDENT
;

block:
   part_declare_vars
   {}
   compost_command
;

part_declare_vars:  
   var
;

var: 
   {} 
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
   IDENT
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
   innitSymbolsTable();

   yyparse();

   cleanSymbolsTable();
   closeMEPAFile();
   fclose(fp);
   return 0;
}