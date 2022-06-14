#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "bicycles.h"
#include "bicycle.h"
#include "parser.h"
#include "reader.h"

int main (int argc, char *argv[]) {
    bicycles_f *bicycles;
    directory_f *directory;
    char *dir_name, bicycle_name[256];
    int action, is_number, buf, bicycle_pos;

    dir_name = parse_command_line (argv, argc);
    bicycles = inicialize_bicycles ();

    fprintf (stdout, YELLOW "[PROCESSANDO] " NC "Iniciando leitura dos logs...\n");
    directory = get_logs (dir_name);
    fprintf (stdout, YELLOW "[PROCESSANDO] " NC "Processando os logs carregados...\n");
    load_logs (directory, dir_name, bicycles);
    fprintf (stdout, GREEN "[PROCESSADO] " NC "Leitura finalizada com sucesso\n\n");

    do {
        fprintf (stdout, "------------------------------ AÇÕES ------------------------------\n\n");
        fprintf (stdout, "1 - Listar bicicletas\n");
        fprintf (stdout, "2 - Apresentar resumo\n");
        fprintf (stdout, "3 - Listar todas as atividades | agrupado por bicicleta, ordenado pela data\n");
        fprintf (stdout, "4 - Listar todas as atividades | agrupado por bicicleta, ordenado pela distancia\n");
        fprintf (stdout, "5 - Listar todas as atividades | ordenado pela subida acumulada\n");
        fprintf (stdout, "6 - Histograma da bicicleta\n");
        fprintf (stdout, "0 - Sair\n\n");
        fprintf (stdout, "Selecione uma ação: ");
        is_number = scanf("%d", &action);

        buf = getchar();;                    

        if (action == 2 || action == 6) {
            fprintf (stdout, "Informe o nome da bicicleta: ");
//            is_number = scanf ("%[^\n]",  bicycle_name);
            while ( !(buf = scanf("%[^\n]",  bicycle_name)) ) {

                while ( (buf = getchar()) != EOF && buf != '\n' )
                    printf("%c = %d\n", buf,buf);
                printf("X%c = %d\n", buf, buf);                    
            }
            fprintf(stdout,"is_number: %d\n", buf);            
            fflush (stdin);
            // fgets (bicycle_name, INPUT_SIZE, stdin);
            // getchar ();
            // scanf ( "%256[^\n]",  bicycle_name);
        }
        fprintf (stdout, "-------------------------------------------------------------------\n\n");
        if (is_number != 1) {
            fprintf (stderr, RED "[ERROR] " NC "Entrada invalida!\n");
            fprintf (stderr, RED "[ERROR] " NC "Encerrando...\n\n");
//            action = getchar();
//            while (action != '\n' && action != EOF)
//                action = getchar();
//            action = 0;
        } else {
            switch (action) {
                case 1: {
                    list_bicycles (bicycles);
                    break;
                }
                case 2: {
                    printf ("Bicleta: %s\n", bicycle_name);

                    // bicycle_pos = already_added (bicycles, bicycle_name);

                    // printf ("posição: %d\n", bicycle_pos);

                    // print_bicycle_resume_log (bicycles->bicycles[bicycle_pos]);
                    break;
                }
                case 3: {
                    printf("vamos de listar por data\n");
                    break;
                }
                case 4: {
                    printf("vamos de listar por distância\n");
                    break;
                }
                case 5: {
                    printf("vamos de listar por subida\n");
                    break;
                }
                case 6: {
                    printf("hora do histograma\n");
                    break;
                }
                default: {
                    printf("%d\n", action);
                    fprintf (stderr, "Comando invalido!\n\n");
                    break;
                }
            }
        }
    } while (action != 0);

    /* limpa os espaços alocados durante a execução do programa */
    clean_bicycles (bicycles);
    clean_directory (directory);
    exit (EXIT_SUCCESS);
}