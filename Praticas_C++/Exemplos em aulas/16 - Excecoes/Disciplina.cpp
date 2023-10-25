#include "Disciplina.hpp"
#include "SalaAula.hpp"

#include<iostream>

Disciplina::Disciplina(std::string nome, SalaAula* sala)
	:nome{nome}, sala(nullptr) {
	this->setSalaAula(sala);
}

Disciplina::~Disciplina(){
	std::cerr << "Destruindo disciplina " << nome << std::endl;
	//o setSalaAula vai remover a disciplina da sala de aula antiga, caso ela exista
	this->setSalaAula(nullptr);
	std::list<ConteudoMinistrado*>::iterator it;
	for(it=conteudos.begin(); it!=conteudos.end(); it++)
		delete *it;//liberando a memória de cada conteúdo
}

void Disciplina::adicionarAluno(Pessoa* aluno){
	this->alunos.push_back(aluno);
}

void Disciplina::removerAluno(Pessoa* aluno){
	this->alunos.remove(aluno);
}

void Disciplina::removerAluno(unsigned long cpf){
	std::list<Pessoa*>::iterator it;

	for(it = this->alunos.begin(); it != this->alunos.end(); it++)
		if((*it)->getCpf() == cpf)
			break;
	if(it != this->alunos.end())
		alunos.erase(it);
}

const std::list<Pessoa*>& Disciplina::getAlunos() const{
	return alunos;
}

std::string Disciplina::getNome(){
	return this->nome;
}

void Disciplina::setNome(std::string nome){
	this->nome = nome;
}

int Disciplina::getCargaHoraria(){
	return this->cargaHoraria;
}

void Disciplina::setCargaHoraria(unsigned int cargaHoraria){
	this->cargaHoraria = cargaHoraria;
}

Professor* Disciplina::getProfessor(){
	return this->professor;
}

void Disciplina::setProfessor(Professor* professor){
	this->professor = professor;
}

void Disciplina::setSalaAula(SalaAula* sala){
	if(this->sala != nullptr)//se já existia uma sala, remover a disciplina dessa sala
		this->sala->removerDisciplina(this);
	this->sala = sala;
	if(this->sala != nullptr)
		this->sala->adicionarDisciplina(this);//adicionar a disciplina na nova sala
}

SalaAula* Disciplina::getSalaAula(){
	return this->sala;
}

void Disciplina::anularSalaAula(){
	this->sala = nullptr;
}

void Disciplina::imprimeDados(std::string& cabecalho, unsigned int& cargaTotalCurso){
	double pctCurso = (double)cargaHoraria/cargaTotalCurso;
	pctCurso = pctCurso * 100;
	std::cout << cabecalho << std::endl;
	std::cout << "Disciplina: " << this->nome << std::endl;
	std::cout << "Carga: " << this->cargaHoraria << std::endl;
	std::cout << "Percentagem do curso: " << pctCurso << "%" << std::endl;
	std::cout << "Professor: " << this->professor->getNome() << std::endl;

}

void Disciplina::adicionarConteudoMinistrado(std::string conteudo, unsigned short cargaHorariaConteudo){
	this->conteudos.push_back(new ConteudoMinistrado{conteudo, cargaHorariaConteudo});
}

void Disciplina::imprimirConteudosMinistrados(){
	std::list<ConteudoMinistrado*>::iterator it;
	for(it = conteudos.begin(); it!=conteudos.end(); it++){
		std::cout << "Id: " << (*it)->getId() << std::endl
			<< "Conteudo: " << (*it)->getDescricao() << std::endl
			<< "Carga: " << (*it)->getCargaHorariaConteudo() << std::endl << std::endl;
	}
}
