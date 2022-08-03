#include "audio.h"

int load_audios (audios_t *audios) {
    if (! (audios->hit = al_load_sample ("./resources/audios/hit.wav")))
        return EXIT_FAILURE;
    if (! (audios->click = al_load_sample ("./resources/audios/click.wav")))
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

void destroy_audios (audios_t *audios) {
    al_destroy_sample (audios->hit);
    al_destroy_sample (audios->click);
}