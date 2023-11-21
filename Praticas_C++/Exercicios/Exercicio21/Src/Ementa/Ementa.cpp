#include "Ementa.hpp"

#include <iostream>

namespace ufpr {
// Constructors
Ementa::Ementa() : livros{std::make_unique<std::list<std::shared_ptr<const Livro>>>()} {}

Ementa::Ementa(const std::string descricao)
    : descricao{descricao}, livros{std::make_unique<std::list<std::shared_ptr<const Livro>>>()} {}

Ementa::Ementa(const Ementa& ementa)
    : descricao{ementa.descricao}, livros{new std::list<std::shared_ptr<const Livro>>{*ementa.livros.get()}} {}

Ementa::Ementa(Ementa&& ementa) : descricao{ementa.descricao}, livros{ementa.livros.release()} {}

// Getters
const std::string& Ementa::getDescricao() const { return this->descricao; }

const std::list<std::shared_ptr<const Livro>>* Ementa::getLivros() const { return this->livros.get(); }

// Setters
void Ementa::setDescricao(const std::string& descricao) { this->descricao = descricao; }

// Functions
void Ementa::addLivro(std::shared_ptr<const Livro> livro) { this->livros->push_back(livro); }

// operators
const Ementa& Ementa::operator=(const Ementa& ementa) {
    if (this == &ementa) return *this;

    this->descricao = ementa.descricao;
    // delete this->livros;
    this->livros = std::make_unique<std::list<std::shared_ptr<const Livro>>>(*ementa.livros);

    return *this;
}

Ementa& Ementa::operator=(Ementa&& ementa) {
    if (this == &ementa) return *this;
    this->descricao = ementa.descricao;

    std::list<std::shared_ptr<const Livro>>* temp{ementa.livros.release()};
    this->livros = std::make_unique<std::list<std::shared_ptr<const Livro>>>(temp);

    // ementa.livros = nullptr;

    return *this;
}
}  // namespace ufpr