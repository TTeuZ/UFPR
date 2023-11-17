#include "Console.hpp"

#include<iostream>

using namespace ufpr;

void Console::imprimirDadosDisciplina(const Disciplina& disciplina){
	std::cout << "Disicplina: "<< disciplina.getNome() << '\n';
	if(disciplina.getProfessor() != nullptr)
		std::cout << "Professor: " << disciplina.getProfessor()->getNome() << '\n';
	else
		std::cout << "Sem professor" << '\n';

	std::cout << "Conteudos Ministrados" << '\n';

        std::list<ConteudoMinistrado*>::const_iterator it;
        for(it = disciplina.getConteudos().begin(); it!=disciplina.getConteudos().end(); it++){
                std::cout << "Id: " << (*it)->getId() << "\nConteudo: " << (*it)->getDescricao()
                        << "\nCarga: " << (*it)->getCargaHorariaConteudo() << "\n\n";

        }
}