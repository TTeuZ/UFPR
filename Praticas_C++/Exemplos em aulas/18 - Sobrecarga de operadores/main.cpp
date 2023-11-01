#include <iostream>
#include <string>

#include "CPF.hpp"
#include "Pessoa.hpp"

int main() {
    ufpr::CPF cpf{11111111111};
    ufpr::CPF cpf2{11111111111};

    if (cpf == cpf2)
        std::cout << "iguais" << std::endl;
    else
        std::cout << "Diferentes" << std::endl;

    return 0;
}