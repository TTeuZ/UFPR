#include "error.h"

void emit_error (int error_code) {
    switch (error_code) {
        case INIT_ERROR:
            fprintf (stderr, RED "[ERROR] " NC "Falha na inicialização da Allegro!\n\n");
            break;
        case READ_GAME_ERROR:
            fprintf (stderr, RED "[ERROR] " NC "Erro ao recuperar a sessão anterior, iniciando novo jogo!\n\n");
            break;
        case READ_POINTS_ERROR:
            fprintf (stderr, RED "[ERROR] " NC "Erro ao recuperar o record e moedas anteriores, iniciando novamente!\n\n");
            break;
        case READ_SHOP_ERROR:
            fprintf (stderr, RED "[ERROR] " NC "Erro ao ler a loja do jogo!\n\n");
            break;
        case SAVE_POINTS_ERROR:
            fprintf (stderr, RED "[ERROR] " NC "Erro ao salvar a pontuação atual!\n\n");
            break;
        case SAVE_GAME_ERROR:
            fprintf (stderr, RED "[ERROR] " NC "Erro ao salvar o jogo atual!\n\n");
            break;
        case SAVE_SHOP_ERROR:
            fprintf (stderr, RED "[ERROR] " NC "Erro ao salvar a loja!\n\n");
            break;
        case GAME_OBJECTS_ERROR:
            fprintf (stderr, RED "[ERROR] " NC "Erro ao iniciar os objetos do jogo!\n\n");
            break;
        case ADD_BALL_ERROR:
            fprintf (stderr, RED "[ERROR] " NC "Erro ao iniciar as bolas do jogo!\n\n");
            break;
    }
}