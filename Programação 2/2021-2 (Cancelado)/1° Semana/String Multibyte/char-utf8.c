#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>

int main()
{
  char *frase = "Olá ɣ 诶 😃" ;

  // ajusta a localização de acordo com o SO
  setlocale (LC_ALL, "") ;

  // conteúdos da string
  printf ("Frase           : %s\n",  frase) ;

  // número de caracteres usando strlen()
  printf ("strlen (frase)  : %ld\n", strlen(frase)) ;

  // número de caracteres usando mbstowcs()
  printf ("mbstowcs (frase): %ld\n", mbstowcs(NULL, frase, 0)) ;
}