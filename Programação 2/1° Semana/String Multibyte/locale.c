#include <stdio.h>
#include <locale.h>

int main()
{
  char *locale ;

  // obtém o LC_CTYPE atual do programa
  locale = setlocale (LC_CTYPE, NULL) ;
  printf ("Current locale is %s\n", locale) ;

  // ajusta o LC_TYPE do programa para o default do SO
  locale = setlocale (LC_CTYPE, "") ;
  if (locale)
    printf ("Current locale is %s\n", locale) ;
  else
    fprintf(stderr, "Can't set the specified locale\n") ;

  // ajusta o LC_TYPE do programa para "pt_BR.iso88591"
  locale = setlocale (LC_CTYPE, "pt_BR.iso88591") ;
  if (locale)
    printf ("Current locale is %s\n", locale) ;
  else
    fprintf(stderr, "Can't set the specified locale\n") ;
}