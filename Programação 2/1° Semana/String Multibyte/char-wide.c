#include <stdio.h>
#include <wchar.h>
#include <locale.h>

int main ()
{
  wchar_t c ;         // um caractere largo
  wchar_t *s ;        // ponteiro para uma string larga

  c = L'a' ;          // caractere constante largo
  s = L"equação" ;    // string constante larga

  // ajusta a localização de acordo com o SO
  setlocale(LC_ALL,"");

  // escrita de caracteres largos
  printf ("O caractere [%lc] tem %ld bytes\n", c, sizeof (c)) ;

  // escrita de strings largas
  printf ("A string [%ls] tem %ld caracteres\n", s, wcslen (s)) ;
}