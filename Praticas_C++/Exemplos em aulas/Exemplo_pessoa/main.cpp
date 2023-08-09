#include <iostream>

#include "Pessoa.hpp"

int main() {
    Pessoa p1;
    int idade;
    std::cout << "Nome: ";
    std::cin >> p1.nome;
    std::cout << "Idade: ";
    std::cin >> idade;
    p1.idade = idade;
    bool valido = false;
    while (!valido) {
        std::cout << "CPF: ";
        std::cin >> p1.cpf;
        valido = p1.validarCPF(p1.cpf);
    }
    std::cout << "Dados da pessoa: " << p1.nome << "\t"
              << (unsigned short int)p1.idade << "\t" << p1.cpf << '\n';
    return 0;
}