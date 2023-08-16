#include <iostream>
#include <string>

#include "Disciplina.hpp"
#include "Pessoa.hpp"

int main() {
    Pessoa *p1{new Pessoa{"Irineu", 11111111111, 20}};

    std::cout << p1->getNome() << '\t' << p1->getIdade() << '\t' << p1->getCpf()
              << std::endl;

    // Pessoa p1{"Joao", 11111111111, 20};
    // Pessoa p2{"Maria"};

    // Disciplina d1{"Orientacao a Objetos"};
    // d1.setProfessor(&p1);

    // std::cout << p1.getNome() << '\t' << p1.getIdade() << '\t' << p1.getCpf()
    //           << '\n';

    // std::cout << d1.getNome() << '\t' << d1.getProfessor()->getNome() <<
    // '\n';

    delete p1;

    return 0;
}