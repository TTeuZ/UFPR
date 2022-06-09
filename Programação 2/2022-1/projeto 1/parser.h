#ifndef PARSER
#define PARSER

/*
* Função que recebe o argv e trata os parametros recebidos da linha de comandos
* Caso o parametro necessário não seja indicado emite erro e encerra o programa
* Caso parametros desnecessários sejam enviados emite erro e encerra o programa
* Em caso de parametros corretos, retorna o parametro
*/
char *parse_command_line (char *argv[], int argc);

#endif