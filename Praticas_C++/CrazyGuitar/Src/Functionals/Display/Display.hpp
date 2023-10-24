#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <allegro5/allegro5.h>

#include <cstdint>

class Display {
   public:
    Display(const uint16_t widht, const uint16_t height);

    virtual ~Display();

   private:
    uint16_t widht;
    uint16_t height;
    ALLEGRO_DISPLAY* display;
    ALLEGRO_BITMAP* buffer;
};

#endif