#include <cstdint>
#include <iostream>
#include <string>

#include "Rectangle.hpp"

#define COLOR_SIZE 50

int main() {
    Rectangle rectangle;
    char color[COLOR_SIZE];
    uint32_t width, height;

    std::cout << "Informe a cor do retangulo: ";
    std::cin.getline(color, COLOR_SIZE);
    rectangle.setColor(color);

    std::cout << "Informe a largura: ";
    std::cin >> width;
    rectangle.setWidth(width);

    std::cout << "Informe a altura: ";
    std::cin >> height;
    rectangle.setHeight(height);

    std::cout << "Retangulo:" << std::endl;
    rectangle.introduce();
    std::cout << "Area: " << rectangle.area() << std::endl;
    std::cout << "Perimetro: " << rectangle.perimeter() << std::endl;

    return 0;
}