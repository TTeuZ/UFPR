#include <iostream>
#include <string>

#include "Disciplina.hpp"
#include "Pessoa.hpp"

int main() {
    Pessoa *p1{new Pessoa{"Irineu", 11111111111, 20}};
    Disciplina *d1{new Disciplina{"Praticas de desenvolvimento de software"}};

    d1->setProfessor(p1);

    std::cout << d1->getNomeProfessor() << std::endl;

    delete p1;
    delete d1;
    return 0;
}