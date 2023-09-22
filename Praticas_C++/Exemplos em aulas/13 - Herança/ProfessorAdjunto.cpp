#include "ProfessorAdjunto.hpp"

// Getters
const std::string& ProfessorAdjunto::getLinhaPesquisa() const {
    return linhaPesquisa;
}

// Setters
void ProfessorAdjunto::setLinhaPesquisa(const std::string& linhaPesquisa) {
    this->linhaPesquisa = linhaPesquisa;
}

// Functions
uint16_t ProfessorAdjunto::getSalario() const {
    return Professor::getSalario() * 1.1;
}
