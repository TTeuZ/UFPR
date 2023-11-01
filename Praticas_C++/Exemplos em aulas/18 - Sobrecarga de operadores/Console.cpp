#include "Console.hpp"

#include<iostream>

using namespace ufpr;

void Console::imprimirDadosDisciplina(const Disciplina& disciplina){
	std::cout << "Disicplina: "<< disciplina.getNome() << std::endl;
	if(disciplina.getProfessor() != nullptr)
		std::cout << "Professor: " << disciplina.getProfessor()->getNome() << std::endl;
	else
		std::cout << "Sem professor" << std::endl;

	std::cout << "Conteudos Ministrados" << std::endl;

        std::list<ConteudoMinistrado*>::const_iterator it;
        for(it = disciplina.getConteudos().begin(); it!=disciplina.getConteudos().end(); it++){
                std::cout << "Id: " << (*it)->getId() << std::endl
                        << "Conteudo: " << (*it)->getDescricao() << std::endl
                        << "Carga: " << (*it)->getCargaHorariaConteudo() << std::endl << std::endl;

        }
}