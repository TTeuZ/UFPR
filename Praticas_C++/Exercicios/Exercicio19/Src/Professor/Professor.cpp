#include "Professor.hpp"

namespace ufpr {
// Constructors
Professor::Professor(const std::string& nome, const uint64_t cpf,
                     const uint16_t valorHora, const uint8_t cargaHoraria)
    : Pessoa{nome, cpf}, valorHora{valorHora}, cargaHoraria{cargaHoraria} {}

// Getters
uint16_t Professor::getValorHora() const { return this->valorHora; }

uint8_t Professor::getCargaHoraria() const { return this->cargaHoraria; }

// Setters
void Professor::setValorHora(const uint16_t valorHora) {
    this->valorHora = valorHora;
}

void Professor::setCargaHoraria(const uint8_t cargaHoraria) {
    this->cargaHoraria = cargaHoraria;
}

// Functions
uint32_t Professor::getSalario() const {
    // assumindo que um mês tem aprox 4.5 semanas
    return this->valorHora * this->cargaHoraria * 4.5;
}
}