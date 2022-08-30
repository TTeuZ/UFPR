#ifndef __AUDIO_H__
#define __AUDIO_H__

#include <allegro5/allegro5.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "../../constants.h"

typedef struct audios {
    ALLEGRO_SAMPLE *hit;
    ALLEGRO_SAMPLE *click;
    ALLEGRO_SAMPLE *buy;
} audios_t;

/*!
    \brief Função que inicializa a estrutura de armazenamento dos sons do jogo
    \param audios Ponteiro de acesso para a estrutura de sons
*/
int load_audios (audios_t *audios);

/*!
    \brief Função responsavel por emitir o audio especificado por parametro
    \param audio Ponteiro de acesso para uma ALLEGRO_SAMPLE
    \param gain Volume do son
    \param speed Velocidade de reprodução
*/
void play_audio (ALLEGRO_SAMPLE *audio, int gain, int speed);

/*!
    \brief Função que desaloca as estruturas de sons alocadas
    \param audios Ponteiro de acesso para a estrutura de sons
*/
void destroy_audios (audios_t *audios);
#endif