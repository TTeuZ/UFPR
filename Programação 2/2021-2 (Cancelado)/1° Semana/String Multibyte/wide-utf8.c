#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <wchar.h>

int main()
{
  int i ;
  char    *frase1 =  "Olá ɣ 诶 😃" ;
  wchar_t *frase2 = L"Olá ɣ 诶 😃" ;

  // ajusta a localização de acordo com o SO
  setlocale(LC_ALL,"");

  // conteúdos das strings
  printf ("Frase 1          : %s\n",  frase1) ;
  printf ("Frase 2          : %ls\n", frase2) ;

  // tamanho em bytes
  printf ("sizeof (char)    : %ld\n", sizeof(char)) ;
  printf ("sizeof (wchar_t) : %ld\n", sizeof(wchar_t)) ;

  // número de caracteres usando strlen()
  printf ("strlen (frase1)  : %ld\n", strlen(frase1)) ;
  printf ("strlen (frase2)  : %ld\n", strlen(frase2)) ;  // incorreto

  // número de caracteres usando wcslen()
  printf ("wcslen (frase1)  : %ld\n", wcslen(frase1)) ;  // incorreto
  printf ("wcslen (frase2)  : %ld\n", wcslen(frase2)) ;

  // número de caracteres usando mbstowcs()
  printf ("mbstowcs (frase1): %ld\n", mbstowcs(NULL, frase1, 0)) ;
  printf ("mbstowcs (frase2): %ld\n", mbstowcs(NULL, frase2, 0)) ; // incorreto

  // percurso por índice, string estreita (narrow)
  printf ("Frase1: ") ;
  for (i=0; i<strlen(frase1); i++)
    printf ("[%c] ", frase1[i]) ;
  printf ("\n") ;

  // percurso por índice, string larga (wide)
  printf ("Frase2: ") ;
  for (i=0; i<wcslen(frase2); i++)
    printf ("[%lc] ", frase2[i]) ;
  printf ("\n") ;
}