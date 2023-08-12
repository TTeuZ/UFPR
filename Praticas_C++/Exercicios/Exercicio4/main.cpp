#include <cstdint>
#include <iostream>
#include <string>

#include "Rectangle.hpp"

#define COLOR_SIZE 50

int main() {
    Rectangle rec1;
    Rectangle rec2{"Azul", 100, 200};
    Rectangle rec3{"Preto", 50};

    std::cout << "Retangulo 1:" << std::endl;
    rec1.introduce();
    std::cout << "Area: " << rec1.area() << std::endl;
    std::cout << "Perimetro: " << rec1.perimeter() << std::endl;

    std::cout << "Retangulo 2:" << std::endl;
    rec2.introduce();
    std::cout << "Area: " << rec2.area() << std::endl;
    std::cout << "Perimetro: " << rec2.perimeter() << std::endl;

    std::cout << "Retangulo 3:" << std::endl;
    rec3.introduce();
    std::cout << "Area: " << rec3.area() << std::endl;
    std::cout << "Perimetro: " << rec3.perimeter() << std::endl;

    return 0;
}