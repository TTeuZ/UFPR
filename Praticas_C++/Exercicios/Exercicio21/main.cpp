#include <iostream>
#include <stdexcept>

#include "./Enums/EnumTipoDisciplina.hpp"
#include "./Exceptions/CPFInvalidoException/CPFInvalidoException.hpp"
#include "./Exceptions/NaoPositivoException/NaoPositivoException.hpp"
#include "./Exceptions/NullPointerException/NullPointerException.hpp"
#include "./Src/Aluno/Aluno.hpp"
#include "./Src/Console/Console.hpp"
#include "./Src/ConteudoMinistrado/ConteudoMinistrado.hpp"
#include "./Src/CPF/CPF.hpp"
#include "./Src/Curso/Curso.hpp"
#include "./Src/Disciplina/Disciplina.hpp"
#include "./Src/Engenheiro/Engenheiro.hpp"
#include "./Src/Pessoa/Pessoa.hpp"
#include "./Src/Professor/Professor.hpp"
#include "./Src/ProfessorAdjunto/ProfessorAdjunto.hpp"
#include "./Src/ProfessorEngenheiro/ProfessorEngenheiro.hpp"
#include "./Src/SalaAula/SalaAula.hpp"

ufpr::Ementa* testEmenta() {
    ufpr::Ementa* temp{new ufpr::Ementa{"temp"}};
    temp->addLivro(ufpr::Livro::carregarLivro(1234));
    temp->addLivro(ufpr::Livro::carregarLivro(5678));

    return temp;
}

int main() {
    ufpr::Ementa* ementa1{new ufpr::Ementa{"Paradigmas de programação"}};
    ufpr::Ementa* ementa2{new ufpr::Ementa{"Orientação a Objetos"}};

    ementa1->addLivro(ufpr::Livro::carregarLivro(1234));
    ementa1->addLivro(ufpr::Livro::carregarLivro(5678));
    ementa2->addLivro(ufpr::Livro::carregarLivro(1234));

    ufpr::Ementa ementa3{*ementa1};
    ufpr::Ementa* ementa4{testEmenta()};

    delete ementa1;
    delete ementa2;
    delete ementa4;

    return 0;
}