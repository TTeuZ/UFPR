#include "ProfessorAdjunto.hpp"

#include<iostream>

ProfessorAdjunto::~ProfessorAdjunto(){
	std::cout << "Destrutor de Professor Adjunto" << std::endl;
}

unsigned int ProfessorAdjunto::getSalario() const{
	return Professor::getSalario() * 1.1;
}
