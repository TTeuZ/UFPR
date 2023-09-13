#include <iostream>

#include "Console.hpp"
#include "ConteudoMinistrado.hpp"
#include "Disciplina.hpp"
#include "Pessoa.hpp"
#include "SalaAula.hpp"

int main() {
    Disciplina dis1{"C++", nullptr};
    Disciplina* dis2{new Disciplina{"Java", nullptr}};

    SalaAula sala{"Lab5", 40};
    dis1.setSalaAula(&sala);
    dis2->setSalaAula(&sala);

    // std::list<Disciplina*> disSala = sala.getDisciplinas();
    // std::list<Disciplina*>::iterator it;
    // for (it = disSala.begin(); it != disSala.end(); ++it)
    //     std::cout << (*it)->getNome() << std::endl;

    delete dis2;
    std::cout << "fim \n";

    return 0;
}