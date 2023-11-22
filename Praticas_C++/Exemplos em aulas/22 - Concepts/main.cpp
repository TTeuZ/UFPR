#include <iostream>

#include "Util.hpp"

int main() {
    std::list<double> valores;
    valores.push_back(1);
    valores.push_back(2);
    valores.push_back(3);

    std::cout << Util<double>::somar(valores) << '\n';

    std::cout << "Fim!!!\n";
    return 0;
}