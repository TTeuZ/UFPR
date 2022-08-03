#include "images.h"

int load_images (images_t *images) {
    if (! (images->sound = al_load_bitmap ("./resources/images/music.png")))
        return EXIT_FAILURE;
    if (! (images->back = al_load_bitmap ("./resources/images/left-arrow.png")))
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

void destroy_images (images_t *images) {
    al_destroy_bitmap (images->sound);
    al_destroy_bitmap (images->back);
}