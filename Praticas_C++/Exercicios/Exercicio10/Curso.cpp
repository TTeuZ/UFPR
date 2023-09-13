#include "Curso.hpp"

// Constructors
Curso::Curso(std::string nome, uint8_t anoCriacao, uint8_t cargaHorariaMinima)
    : nome(nome),
      anoCriacao(anoCriacao),
      cargaHorariaMinima(cargaHorariaMinima) {}

// Getters
std::string& Curso::getNome() { return this->nome; }

uint8_t Curso::getAnoCriacao() { return this->anoCriacao; };

uint8_t Curso::getCargaHorariaMinima() { return this->cargaHorariaMinima; };

// Setters
void Curso::setNome(std::string nome) { this->nome = nome; };

void Curso::setCargaHorariaMinima(uint8_t cargaHorariaMinima) {
    this->cargaHorariaMinima = cargaHorariaMinima > 0 ? cargaHorariaMinima : 0;
};