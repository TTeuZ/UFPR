#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <cstdint>
#include <string>

class Rectangle {
   public:
    // Constructors
    Rectangle();
    Rectangle(std::string color, uint32_t width = 100, uint32_t height = 100);

    // Getters
    std::string getColor();
    uint32_t getWidth();
    uint32_t getHeight();

    // Setters
    void setColor(std::string newColor);
    void setWidth(uint32_t newWidth);
    void setHeight(uint32_t newHeight);

    // Funtcions
    void introduce();
    uint32_t perimeter();
    uint32_t area();

   private:
    std::string color;
    uint32_t width;
    uint32_t height;
};

#endif