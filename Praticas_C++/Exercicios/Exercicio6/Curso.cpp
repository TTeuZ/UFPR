#include "Curso.hpp"

// Constructors
Curso::Curso(std::string nome, int8_t anoCriacao, int8_t cargaHorariaMinima)
    : nome(nome),
      anoCriacao(anoCriacao),
      cargaHorariaMinima(cargaHorariaMinima) {}

// Getters
std::string Curso::getNome() { return this->nome; }

int8_t Curso::getAnoCriacao() { return this->anoCriacao; };

int8_t Curso::getCargaHorariaMinima() { return this->cargaHorariaMinima; };

// Setters
void Curso::setNome(std::string nome) { this->nome = nome; };

void Curso::setCargaHorariaMinima(int8_t cargaHorariaMinima) {
    this->cargaHorariaMinima = cargaHorariaMinima > 0 ? cargaHorariaMinima : 0;
};