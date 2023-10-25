#include "SalaAula.hpp"
#include <iostream>

SalaAula::SalaAula(std::string nome, unsigned int capacidade)
	:nome{nome}, capacidade{capacidade}{
}

SalaAula::~SalaAula(){
	std::cerr << "Destruindo Sala " << nome << std::endl;
	std::list<Disciplina*>::iterator it{disciplinasMinistradas.begin()};
	for( ; it != disciplinasMinistradas.end(); it++)
		(*it)->anularSalaAula();
}
    
std::string SalaAula::getNome(){
	return nome;
}

void SalaAula::setNome(std::string nome){
	this->nome = nome;
}

unsigned int SalaAula::getCapacidade(){
	return capacidade;
}

void SalaAula::setCapcidade(unsigned int capacidade){
	this->capacidade = capacidade;
}

void SalaAula::adicionarDisciplina(Disciplina* disciplina){
	disciplinasMinistradas.push_back(disciplina);
}

void SalaAula::removerDisciplina(Disciplina* disciplina){
	disciplinasMinistradas.remove(disciplina);
}

std::list<Disciplina*>& SalaAula::getDisciplinas(){
	return disciplinasMinistradas;
}
