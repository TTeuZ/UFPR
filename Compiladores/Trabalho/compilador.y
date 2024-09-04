%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "compilador.h"

int num_vars;
%}

%token PROGRAM ABRE_PARENTESES FECHA_PARENTESES
%token VIRGULA PONTO_E_VIRGULA DOIS_PONTOS PONTO
%token T_BEGIN T_END VAR IDENT ATRIBUICAO

%%

programa:
   {
      geraCodigo (NULL, "INPP");
   }
   PROGRAM IDENT
   ABRE_PARENTESES lista_idents FECHA_PARENTESES PONTO_E_VIRGULA
   bloco PONTO 
   {
      geraCodigo (NULL, "PARA");
   }
;

bloco:
   parte_declara_vars
   {}
   comando_composto
;

parte_declara_vars:  
   var
;

var: 
   {} 
   VAR declara_vars
   |
;

declara_vars: 
   declara_vars declara_var
   | declara_var
;

declara_var: 
   {}
   lista_id_var DOIS_PONTOS
   tipo
   {}
   PONTO_E_VIRGULA
;

tipo: 
   IDENT
;

lista_id_var: 
   lista_id_var VIRGULA IDENT
   {}
   | IDENT 
   {}
;

lista_idents: 
   lista_idents VIRGULA IDENT
   | IDENT
;

comando_composto: 
   T_BEGIN comandos T_END
;

comandos:
;

%%

int main (int argc, char** argv) {
   extern FILE* yyin;
   FILE* fp;

   if (argc < 2 || argc > 2) {
      printf("usage compilador <arq>a %d\n", argc);
      return(-1);
   }

   fp = fopen(argv[1], "r");
   if (fp == NULL) {
      printf("usage compilador <arq>b\n");
      return(-1);
   }

   yyin = fp;
   yyparse();

   return 0;
}