#include "Engenheiro.hpp"

using namespace ufpr;

// Constructors
Engenheiro::Engenheiro(const std::string& nome, const uint64_t cpf,
                       const uint16_t numeroCrea)
    : Pessoa{nome, cpf}, numeroCrea(numeroCrea) {}

// Getters
uint16_t Engenheiro::getNumeroCrea() const { return this->numeroCrea; }

// Setters
void Engenheiro::setNumeroCrea(const uint16_t numeroCrea) {
    this->numeroCrea = numeroCrea;
}

// Functions
uint32_t Engenheiro::getSalario() const { return Engenheiro::salarioPadrâo; }