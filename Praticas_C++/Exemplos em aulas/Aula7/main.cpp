#include <iostream>
#include <list>
#include <string>

#include "Disciplina.hpp"
#include "Pessoa.hpp"

int main() {
    std::list<Pessoa *> pessoas;
    Pessoa *p1{new Pessoa{"pedro", 11111111111, 20}};
    Pessoa *p2{new Pessoa{"pedro", 11111111111, 20}};
    Pessoa *p3{new Pessoa{"maria", 11111111111, 20}};

    pessoas.push_back(p1);
    pessoas.push_back(p2);
    pessoas.push_back(p3);

    std::list<Pessoa *>::iterator it;
    for (it = pessoas.begin(); it != pessoas.end(); ++it) {
        if ((*it)->getNome() == "pedro") {
            Pessoa *ptr{*it};
            it = pessoas.erase(it);
            it--;
            delete ptr;
        }
    }

    for (it = pessoas.begin(); it != pessoas.end(); ++it) {
        std::cout << "Pessoa: " << (*it)->getNome() << std::endl;
        delete *it;
    }

    return 0;
}