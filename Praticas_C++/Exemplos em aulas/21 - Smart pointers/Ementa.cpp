#include "Ementa.hpp"

#include <iostream>

namespace ufpr{

Ementa::Ementa():livros{new std::list<std::shared_ptr<const Livro>>}{}

Ementa::Ementa(const std::string descricao)
        :descricao{descricao}, livros{new std::list<std::shared_ptr<const Livro>>}{
    std::cout << "Criando ementa " << descricao << std::endl;
}

Ementa::Ementa(const Ementa& ementa)
        :descricao{ementa.descricao}, livros{new std::list<std::shared_ptr<const Livro>>{*ementa.livros}}{
    std::cout << "Copiando ementa " << descricao << std::endl;

}

Ementa::Ementa(Ementa&& ementa)
        :descricao{ementa.descricao}, livros{ementa.livros}{
    ementa.livros = nullptr;
    std::cout << "Move constructor " << descricao << std::endl;
}

Ementa::~Ementa(){
    std::cout << "Destrutor de " << this->descricao << '\n';
    if(livros!=nullptr)
        delete livros;
}

void Ementa::setDescricao(const std::string& descricao){
    this->descricao = descricao;
}

const std::string& Ementa::getDescricao() const{
    return this->descricao;
}

void Ementa::addLivro(std::shared_ptr<const Livro> livro){
    this->livros->push_back(livro);
}

const std::list<std::shared_ptr<const Livro>>* Ementa::getLivros() const{
    return this->livros;
}

Ementa& Ementa::operator=(Ementa&& ementa){
    if(this == &ementa)
        return *this;
    this->descricao = ementa.descricao;
    this->livros = ementa.livros;
    ementa.livros = nullptr;

    std::cout << "Move Assignment" << '\n';

    return *this;
}

const Ementa& Ementa::operator=(const Ementa& ementa){
    if(this == &ementa)
        return *this;
    this->descricao = ementa.descricao;
    delete this->livros;
    this->livros = new std::list<std::shared_ptr<const Livro>>{*ementa.livros};

    std::cout << "Operador de atribuiução" << '\n';

    return *this;
}

}