#include "audio.h"

int load_audios (audios_t *audios) {
    if (! (audios->hit = al_load_sample ("./resources/audios/hit.wav")))
        return EXIT_FAILURE;
    if (! (audios->click = al_load_sample ("./resources/audios/click.wav")))
        return EXIT_FAILURE;
    if (! (audios->buy = al_load_sample ("./resources/audios/buy.wav")))
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

void play_audio (ALLEGRO_SAMPLE *audio, int gain, int speed) {
    al_play_sample (audio, gain, 0.0, speed, ALLEGRO_PLAYMODE_ONCE, NULL);
}

void destroy_audios (audios_t *audios) {
    al_destroy_sample (audios->hit);
    al_destroy_sample (audios->click);
    al_destroy_sample (audios->buy);
}