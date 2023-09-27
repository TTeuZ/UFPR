#include "ProfessorAdjunto.hpp"

#include <iostream>

// Destructor
ProfessorAdjunto::~ProfessorAdjunto() {
    std::cout << "Destruiu professor Adjunto" << std::endl;
}

// Getters
const std::string& ProfessorAdjunto::getLinhaPesquisa() const {
    return this->linhaPesquisa;
}

// Setters
void ProfessorAdjunto::setLinhaPesquisa(const std::string& linhaPesquisa) {
    this->linhaPesquisa = linhaPesquisa;
}

// Functions
uint32_t ProfessorAdjunto::getSalario() const {
    return Professor::getSalario() * 1.1;
}
