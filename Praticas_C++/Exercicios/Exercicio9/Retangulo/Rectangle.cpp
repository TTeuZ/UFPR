#include "Rectangle.hpp"

#include <iostream>
#include <string>

uint64_t Rectangle::qty{0};

// Constructors
Rectangle::Rectangle() : color{"black"}, width{10}, height{10} {
    Rectangle::qty++;
};

Rectangle::Rectangle(std::string color, uint32_t width, uint32_t height)
    : color{color} {
    Rectangle::qty++;
    setWidth(width);
    setHeight(height);
}

// Getters
std::string Rectangle::getColor() { return color; };

uint32_t Rectangle::getWidth() { return width; };

uint32_t Rectangle::getHeight() { return height; };

// Setters
void Rectangle::setColor(std::string newColor) { color = newColor; };

void Rectangle::setWidth(uint32_t newWidth) {
    width = newWidth > 0 ? newWidth : 0;
};

void Rectangle::setHeight(uint32_t newHeight) {
    height = newHeight > 0 ? newHeight : 0;
};

// Functions
void Rectangle::introduce() {
    std::cout << "\tCor de preenchimento: " << color << std::endl;
    std::cout << "\tLargura: " << width << std::endl;
    std::cout << "\tAltura: " << height << std::endl;
}

uint32_t Rectangle::perimeter() { return (height * 2) + (width * 2); };

uint32_t Rectangle::area() { return height * width; };

uint64_t Rectangle::getRectanglesQty() { return Rectangle::qty; }
