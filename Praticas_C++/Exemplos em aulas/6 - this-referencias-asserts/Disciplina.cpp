#include "Disciplina.hpp"

#include <iostream>

Disciplina::Disciplina(std::string nomeDisciplina) : nome{nomeDisciplina} {}

std::string Disciplina::getNome() { return nome; }

void Disciplina::setNome(std::string novoNome) { nome = novoNome; }

int Disciplina::getCargaHoraria() { return cargaHoraria; }

void Disciplina::setCargaHoraria(unsigned int novaCarga) {
    cargaHoraria = novaCarga;
}

Pessoa* Disciplina::getProfessor() { return professor; }

void Disciplina::setProfessor(Pessoa* novoProfessor) {
    professor = novoProfessor;
}

// com o & estamos passando a referencia
// slides para ver a diferença de ponteiro e referencia
// Por enquanto vamos ter que lembrar que temos que armazenar o que passamos
// pela referencia em variaveis, pois por debaixo funciona como um ponteiro
void Disciplina::imprimirDados(std::string& cabecalho,
                               unsigned int cargaTotalCurso) {
    // Não copiei a função
}