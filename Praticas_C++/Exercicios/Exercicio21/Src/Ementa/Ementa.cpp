#include "Ementa.hpp"

#include <iostream>

namespace ufpr {
// Constructors
Ementa::Ementa() : livros{std::make_unique<std::list<std::shared_ptr<const Livro>>>()} {
    std::cout << "Normal1 constructor" << std::endl;
}

Ementa::Ementa(const std::string descricao)
    : descricao{descricao}, livros{std::make_unique<std::list<std::shared_ptr<const Livro>>>()} {
    std::cout << "Normal2 constructor" << std::endl;
}

Ementa::Ementa(const Ementa& ementa)
    : descricao{ementa.descricao}, livros{new std::list<std::shared_ptr<const Livro>>{*ementa.livros}} {
    std::cout << "Copy constructor" << std::endl;
}

Ementa::Ementa(Ementa&& ementa) : descricao{ementa.descricao}, livros{ementa.livros.release()} {
    std::cout << "Move constructor" << std::endl;
}

// Getters
const std::string& Ementa::getDescricao() const { return this->descricao; }

const std::list<std::shared_ptr<const Livro>>* Ementa::getLivros() const { return this->livros.get(); }

// Setters
void Ementa::setDescricao(const std::string& descricao) { this->descricao = descricao; }

// Functions
void Ementa::addLivro(std::shared_ptr<const Livro> livro) { this->livros->push_back(livro); }

// operators
const Ementa& Ementa::operator=(const Ementa& ementa) {
    std::cout << "assignment operator" << std::endl;

    if (this == &ementa) return *this;

    this->descricao = ementa.descricao;
    this->livros.reset(new std::list<std::shared_ptr<const Livro>>{*ementa.livros});

    return *this;
}

Ementa& Ementa::operator=(Ementa&& ementa) {
    std::cout << "Move assignment" << std::endl;

    if (this == &ementa) return *this;

    this->descricao = ementa.descricao;
    this->livros.reset(ementa.livros.release());

    return *this;
}
}  // namespace ufpr