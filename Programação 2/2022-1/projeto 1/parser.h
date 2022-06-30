#ifndef PARSER
#define PARSER

/*
*   Função que recebe o argv e trata os parametros recebidos da linha de comandos
*   Caso o parametro necessário não seja indicado emite erro
*   Caso parametros desnecessários sejam enviados emite erro
*   Em caso de parametros corretos, retorna o nome da diretório
*/
char *parse_command_line (char *argv[], int argc);

#endif