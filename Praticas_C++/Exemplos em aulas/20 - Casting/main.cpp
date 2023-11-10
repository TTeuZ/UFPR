#include <iostream>

#include "CPF.hpp"

void imprimirCpf(const ufpr::CPF& cpf) {
    std::cout << "O CPF eh: " << cpf << std::endl;
}

int main() {
    ufpr::CPF cpf{11111111111};

    imprimirCpf(cpf);
    // imprimirCpf(22222222222);

    return 0;
}