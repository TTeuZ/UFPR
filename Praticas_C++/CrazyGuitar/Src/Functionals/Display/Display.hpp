#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <allegro5/allegro5.h>

#include <cstdint>

class Display {
   public:
    /**
     * Instanciate an allegro display and an allegro bitmap with the respective
     * width and height
     *
     * @param width Game display width
     * @param height Game DIsplay height
     */
    Display(const uint16_t widht, const uint16_t height);

    /**
     * Free the memory allocated for the allego display and bitmap
     */
    virtual ~Display();

    // TODO: Getters
    // TODO: Function to flip display

   private:
    uint16_t widht;
    uint16_t height;
    ALLEGRO_DISPLAY* display;
    ALLEGRO_BITMAP* buffer;
};

#endif