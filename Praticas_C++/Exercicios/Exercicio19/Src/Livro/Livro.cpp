#include "Livro.hpp"

namespace ufpr {
// Constructor
Livro::Livro(const std::string& titulo, const uint8_t ano)
    : titulo{titulo}, ano{ano} {}

// Getters
const std::string& Livro::getTitulo() const { return this->titulo; }

const uint8_t Livro::getAno() const { return this->ano; }

const std::string& Livro::getAbstract() const { return this->abstract; }

const std::list<std::string>& Livro::getAutores() const {
    return this->autores;
}

// Setters
void Livro::setAbstract(const std::string& abstract) {
    this->abstract = abstract;
}

// Functions
void Livro::addAutor(const std::string& autor) {
    this->autores.push_back(autor);
}
}  // namespace ufpr