#include "Rectangle.hpp"

#include <iostream>

void Rectangle::introduce(const Rectangle rec) {
    std::cout << "\tCor de preenchimento: " << rec.color << std::endl;
    std::cout << "\tLargura: " << rec.width << std::endl;
    std::cout << "\tAltura: " << rec.height << std::endl;
}