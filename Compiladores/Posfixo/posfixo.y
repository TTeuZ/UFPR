
%{
#include <stdio.h>
#include <stdlib.h>

int hasBool = 0;
int hasInt = 0;

int yylex(void);
void hasError();
void yyerror(const char *s);
%}

%token IDENTA IDENTB MAIS MENOS AND OR ASTERISCO DIV ABRE_PARENTESES FECHA_PARENTESES

%%

expr: 
   expr MAIS termo { 
      hasError();
      printf("+"); 
   } |
   expr MENOS termo { 
      hasError();
      printf("-"); 
   } | 
   expr OR fator { 
      hasError();
      printf("or"); 
   } |
   expr AND fator { 
      hasError(); 
      printf("and"); 
   } |
   termo
;

termo: 
   termo ASTERISCO fator  { printf("*"); } | 
   termo DIV fator  { printf("/"); } |
   fator 
;

fator: 
   IDENTA { 
      hasInt = 1;
      printf("A"); 
   } |
   IDENTB { 
      hasBool = 1;
      printf("B"); 
   }
;

%%

void hasError() {
   if (hasInt == 1 && hasBool == 1) {
      yyerror("syntax error");
      exit(EXIT_FAILURE);
   }
}

int main (int argc, char** argv) {
   yyparse();
   printf("\n");
   return EXIT_SUCCESS;
}