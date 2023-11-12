#include "ProfessorAdjunto.hpp"

namespace ufpr {
// Constructors
ProfessorAdjunto::ProfessorAdjunto(const std::string& nome, const CPF& cpf, const uint16_t valorHora,
                                   const uint8_t cargaHoraria)
    : Pessoa{nome, cpf}, Professor{nome, cpf, valorHora, cargaHoraria} {}

// Getters
const std::string& ProfessorAdjunto::getLinhaPesquisa() const { return this->linhaPesquisa; }

// Setters
void ProfessorAdjunto::setLinhaPesquisa(const std::string& linhaPesquisa) { this->linhaPesquisa = linhaPesquisa; }

// Functions
uint32_t ProfessorAdjunto::getSalario() const { return Professor::getSalario() * 1.1; }
}  // namespace ufpr