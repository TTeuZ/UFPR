#include "Display.hpp"

Display::Display(const uint16_t widht, const uint16_t height)
    : widht{widht}, height{height} {
    // TODO: Add exception treatment
    this->display = al_create_display(this->widht, this->height);
    this->buffer = al_create_bitmap(this->widht, this->height);
}

Display::~Display() {
    al_destroy_display(this->display);
    al_destroy_bitmap(this->buffer);
}