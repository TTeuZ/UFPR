#include "ProfessorAdjunto.hpp"

using namespace ufpr;

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
