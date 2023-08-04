#include <iostream>

#include "Rectangle.hpp"

int main() {
    Rectangle rectangles[3];

    for (int i{0}; i < 3; ++i) {
        std::cout << "Informe a cor: ";
        std::cin >> rectangles[i].color;

        std::cout << "Informe a largura: ";
        std::cin >> rectangles[i].width;

        std::cout << "Informe a altura: ";
        std::cin >> rectangles[i].height;
    }

    for (int i{0}; i < 3; ++i) {
        std::cout << "Retangulo " << i + 1 << std::endl;
        rectangles[i].introduce(rectangles[i]);
        std::cout << std::endl;
    }

    return 0;
}