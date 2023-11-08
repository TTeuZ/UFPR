#include "Ementa.hpp"

#include <iostream>

namespace ufpr {

Ementa::Ementa() : livros{new std::list<Livro>} {
    std::cout << "construtor 1" << std::endl;
}

Ementa::Ementa(const std::string descricao)
    : descricao{descricao}, livros{new std::list<Livro>} {
    std::cout << "construtor 2" << std::endl;
}

Ementa::Ementa(Ementa&& ementa)
    : descricao{ementa.descricao}, livros{ementa.livros} {
    ementa.livros = nullptr;
    std::cout << "construtor MOVE" << std::endl;
}

Ementa::Ementa(const Ementa& ementa)
    : descricao{ementa.descricao},
      livros{new std::list<Livro>{*ementa.livros}} {
    std::cout << "construtor copia" << std::endl;
}

Ementa::~Ementa() {
    if (this->livros != nullptr) delete this->livros;
}

void Ementa::setDescricao(const std::string& descricao) {
    this->descricao = descricao;
}

const std::string& Ementa::getDescricao() const { return this->descricao; }

void Ementa::addLivro(const Livro& livro) { this->livros->push_back(livro); }

const std::list<Livro>* Ementa::getLivros() const { return this->livros; }

// operators
const Ementa& Ementa::operator=(const Ementa& ementa) {
    if (this == &ementa) return *this;

    this->descricao = ementa.descricao;
    delete this->livros;
    this->livros = new std::list<Livro>{*ementa.livros};

    return *this;
}

Ementa& Ementa::operator=(Ementa&& ementa) {
    if (this == &ementa) return *this;

    this->descricao = ementa.descricao;
    delete this->livros;
    this->livros = ementa.livros;
    ementa.livros = nullptr;

    return *this;
}
}  // namespace ufpr