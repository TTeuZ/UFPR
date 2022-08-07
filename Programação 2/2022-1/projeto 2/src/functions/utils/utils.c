#include "utils.h"

void start_game_conditions (game_cond_t *game_cond) {
    game_cond->all_init = 1;
    game_cond->redraw = 1;
    game_cond->in_home_page = 1;
    game_cond->in_help_page = 0;
    game_cond->in_pause_page = 0;
    game_cond->in_game_page = 0;
    game_cond->sound_on = 1;
    game_cond->restart = 0;
    game_cond->close_game = 0;
}

void set_pages_to_false (game_cond_t *game_cond) {
    game_cond->in_home_page = 0;
    game_cond->in_help_page = 0;
    game_cond->in_pause_page = 0;
    game_cond->in_game_page = 0;
}

void emit_error (int error_code) {
    switch (error_code) {
        case INIT_ERROR:
            fprintf (stderr, RED "[ERROR] " NC "Falha na inicialização da Allegro!\n\n");
            break;
        case READ_GAME_ERROR:
            fprintf (stderr, RED "[ERROR] " NC "Erro ao recuperar a sessão anterior, iniciando novo jogo!\n\n");
            break;
        case SAVE_POINTS_ERROR:
            fprintf (stderr, RED "[ERROR] " NC "Erro ao salvar a pontuação atual!\n\n");
            break;
        case SAVE_GAME_ERROR:
            fprintf (stderr, RED "[ERROR] " NC "Erro ao salvar o jogo atual!\n\n");
            break;
        case ADD_BALL_ERROR:
            fprintf (stderr, RED "[ERROR] " NC "Erro ao iniciar as bolas do jogo!\n\n");
            break;
    }
}