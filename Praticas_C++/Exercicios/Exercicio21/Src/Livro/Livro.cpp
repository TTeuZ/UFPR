#include "Livro.hpp"

namespace ufpr {
std::unordered_map<uint64_t, std::weak_ptr<const Livro>> Livro::cache;

// Constructor
Livro::Livro(const uint64_t ISBN, const std::string& titulo, const uint8_t ano)
    : ISBN{ISBN}, titulo{titulo}, ano{ano} {}

// Getters
const uint64_t Livro::getISBN() const { return this->ISBN; }

const std::string& Livro::getTitulo() const { return this->titulo; }

const uint8_t Livro::getAno() const { return this->ano; }

const std::string& Livro::getAbstract() const { return this->abstract; }

const std::list<std::string>& Livro::getAutores() const { return this->autores; }

// Setters
void Livro::setAbstract(const std::string& abstract) { this->abstract = abstract; }

// Functions
void Livro::addAutor(const std::string& autor) { this->autores.push_back(autor); }

std::shared_ptr<const Livro> Livro::carregarLivro(const uint64_t ISBN) {
    // abaixo a carga seria feita de um banco de dados.
    // vamos apenas simular colocando alguns dados no livro
    std::unordered_map<unsigned long, std::weak_ptr<const Livro>>::const_iterator it{Livro::cache.find(ISBN)};
    if (it != Livro::cache.end()) {
        std::shared_ptr<const Livro> sptrLivro{it->second.lock()};
        if (sptrLivro != nullptr) return sptrLivro;
    }

    std::string nomeLivro{"Nome do Livro " + std::to_string(ISBN)};
    std::shared_ptr<const Livro> livro{new Livro{ISBN, nomeLivro, 1999}};
    Livro::cache[ISBN] = livro;
    return livro;
}

// Operators
bool Livro::operator==(const Livro& outro) const { return (this->ISBN == outro.ISBN); }

bool Livro::operator!=(const Livro& outro) const { return !(*this == outro); }
}  // namespace ufpr