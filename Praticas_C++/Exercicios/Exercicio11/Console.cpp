#include "Console.hpp"

#include <iostream>

// Destructor
Console::~Console(){};

void Console::imprimirDadosDisciplina(const Disciplina& disciplina) {
    std::cout << "Disicplina: " << disciplina.getNome() << std::endl;
    if (disciplina.getProfessor() != nullptr)
        std::cout << "Professor: " << disciplina.getProfessor()->getNome()
                  << std::endl;
    else
        std::cout << "Sem professor" << std::endl;

    std::cout << "Conteudos Ministrados" << std::endl;
    std::list<ConteudoMinistrado*>::const_iterator it;
    for (it = disciplina.getConteudos().begin();
         it != disciplina.getConteudos().end(); ++it) {
        std::cout << "Id: " << (*it)->getId() << std::endl
                  << "Conteudo: " << (*it)->getDescricao() << std::endl
                  << "Carga: " << (int)(*it)->getCargaHorariaConteudo()
                  << std::endl
                  << std::endl;
    }

    std::cout << "Alunos" << std::endl;
    std::list<const Pessoa*>::const_iterator it_pessoa;
    for (it_pessoa = disciplina.getAlunos().begin();
         it_pessoa != disciplina.getAlunos().end(); ++it_pessoa) {
        std::cout << "Nome: " << (*it_pessoa)->getNome() << std::endl
                  << std::endl;
    }
}
