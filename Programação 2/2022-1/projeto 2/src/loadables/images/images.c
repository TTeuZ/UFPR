#include "images.h"

int load_images (images_t *images) {
    if (! (images->sound = al_load_bitmap ("./resources/images/music.png")))
        return EXIT_FAILURE;
    if (! (images->back = al_load_bitmap ("./resources/images/left-arrow.png")))
        return EXIT_FAILURE;
    if (! (images->pause = al_load_bitmap ("./resources/images/pause.png")))
        return EXIT_FAILURE;
    if (! (images->balls = al_load_bitmap ("./resources/images/balls.png")))
        return EXIT_FAILURE;
    if (! (images->lock = al_load_bitmap ("./resources/images/lock.png")))
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

void destroy_images (images_t *images) {
    al_destroy_bitmap (images->sound);
    al_destroy_bitmap (images->back);
    al_destroy_bitmap (images->pause);
    al_destroy_bitmap (images->balls);
    al_destroy_bitmap (images->lock);
}