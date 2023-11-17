#include "Livro.hpp"

#include <iostream>

namespace ufpr {

std::unordered_map<unsigned long, std::weak_ptr<const Livro>> Livro::cache;

Livro::Livro(const unsigned long ISBN, const std::string& titulo,
             const short int ano)
    : ISBN{ISBN}, titulo{titulo}, ano{ano} {}

Livro::~Livro() { std::cout << "Deletando Livro " << titulo << '\n'; }

unsigned long Livro::getISBN() const { return this->ISBN; }

const std::string& Livro::getTitulo() const { return this->titulo; }

void Livro::setAbstract(const std::string& abstract) {
    this->abstract = abstract;
}

const std::string& Livro::getAbstract() const { return this->abstract; }

const short int Livro::getAno() const { return this->ano; }

void Livro::addAutor(const std::string& autor) {
    this->autores.push_back(autor);
}

const std::list<std::string>& Livro::getAutores() const {
    return this->autores;
}

std::shared_ptr<const Livro> Livro::carregarLivro(const unsigned long ISBN) {
    // abaixo a carga seria feita de um banco de dados.
    // vamos apenas simular colocando alguns dados no livro
    std::unordered_map<unsigned long,
                       std::shared_ptr<const Livro>>::const_iterator it{
        Livro::cache.find(ISBN)};
    if (it != Livro::cache.end()) {
        std::cout << "Livro de ISBN " << ISBN << " na cache\n";
        return it->second;
    }
    std::cout << "Carregando livro de ISBN " << ISBN << '\n';
    std::string nomeLivro{"Nome do Livro " + std::to_string(ISBN)};
    std::shared_ptr<const Livro> livro{new Livro{ISBN, nomeLivro, 1999}};
    Livro::cache[ISBN] = livro;
    return livro;
}

}  // namespace ufpr
