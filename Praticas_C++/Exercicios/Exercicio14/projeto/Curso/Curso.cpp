#include "Curso.hpp"

// Constructors
Curso::Curso(const std::string& nome, const uint8_t anoCriacao,
             const uint8_t cargaHorariaMinima)
    : nome(nome),
      anoCriacao(anoCriacao),
      cargaHorariaMinima(cargaHorariaMinima) {}

// Getters
const std::string& Curso::getNome() const { return this->nome; }

uint8_t Curso::getAnoCriacao() const { return this->anoCriacao; };

uint8_t Curso::getCargaHorariaMinima() const {
    return this->cargaHorariaMinima;
};

// Setters
void Curso::setNome(const std::string& nome) { this->nome = nome; };

void Curso::setCargaHorariaMinima(const uint8_t cargaHorariaMinima) {
    this->cargaHorariaMinima = cargaHorariaMinima > 0 ? cargaHorariaMinima : 0;
};