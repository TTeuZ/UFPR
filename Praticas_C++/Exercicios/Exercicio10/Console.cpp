#include "Console.hpp"

#include <iostream>

// Destructor
Console::~Console(){};

void Console::imprimirDadosDisciplina(Disciplina& disciplina) {
    std::cout << "Disicplina: " << disciplina.getNome() << std::endl;
    if (disciplina.getProfessor() != nullptr)
        std::cout << "Professor: " << disciplina.getProfessor()->getNome()
                  << std::endl;
    else
        std::cout << "Sem professor" << std::endl;

    std::cout << "Conteudos Ministrados" << std::endl;

    std::list<ConteudoMinistrado*>::iterator it;
    for (it = disciplina.getConteudos().begin();
         it != disciplina.getConteudos().end(); ++it) {
        std::cout << "Id: " << (*it)->getId() << std::endl
                  << "Conteudo: " << (*it)->getDescricao() << std::endl
                  << "Carga: " << (int)(*it)->getCargaHorariaConteudo()
                  << std::endl
                  << std::endl;
    }
}
