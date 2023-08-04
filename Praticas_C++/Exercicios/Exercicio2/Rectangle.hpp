#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <cstdint>

class Rectangle {
   public:
    void introduce(Rectangle rec);

    char color[20];
    uint32_t width;
    uint32_t height;
};

#endif