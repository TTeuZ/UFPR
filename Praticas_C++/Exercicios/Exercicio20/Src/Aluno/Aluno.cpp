#include "Aluno.hpp"

namespace ufpr {
// Constructors
Aluno::Aluno(const std::string& nome, const CPF& cpf, const uint64_t grr, const double ira)
    : Pessoa{nome, cpf}, grr{grr}, ira{ira} {}

// Getters
uint64_t Aluno::getGrr() const { return this->grr; }

double Aluno::getIra() const { return this->ira; }

// Setters
void Aluno::setGrr(const uint64_t grr) { this->grr = grr; }

void Aluno::setIra(const double ira) { this->ira = ira; }
}  // namespace ufpr