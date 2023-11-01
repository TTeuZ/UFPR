#include "ProfessorAdjunto.hpp"

using namespace ufpr;

ProfessorAdjunto::~ProfessorAdjunto(){

}

const std::string& ProfessorAdjunto::getLinhaPesquisa() const{
    return this->linhaPesquisa;
}

void ProfessorAdjunto::setLinhaPesquisa(const std::string& linhaPesquisa){
    this->linhaPesquisa = linhaPesquisa;
}

unsigned int ProfessorAdjunto::getSalario() const{
    return Professor::getSalario() * 1.1;
}