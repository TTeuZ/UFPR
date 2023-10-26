#include <iostream>
#include <stdexcept>

#include "./Aluno/Aluno.hpp"
#include "./Console/Console.hpp"
#include "./ConteudoMinistrado/ConteudoMinistrado.hpp"
#include "./Curso/Curso.hpp"
#include "./Disciplina/Disciplina.hpp"
#include "./Engenheiro/Engenheiro.hpp"
#include "./Pessoa/Pessoa.hpp"
#include "./Professor/Professor.hpp"
#include "./ProfessorAdjunto/ProfessorAdjunto.hpp"
#include "./ProfessorEngenheiro/ProfessorEngenheiro.hpp"
#include "./SalaAula/SalaAula.hpp"

int main() {
    Curso *c;
    Disciplina *d;
    try {
        c = new Curso{"Batata", (unsigned char)2023, (unsigned char)3000};
        d = new Disciplina{*c, "Pão de batata 1", nullptr};
    } catch (std::bad_alloc &e) {
        std::cout << "Erro de alocação - " << e.what() << std::endl;
        return 1;
    } catch (NaoPositivoException &e) {
        std::cout << e.what() << " - " << e.desc << std::endl;
        return 1;
    }

    try {
        d->adicionarAluno(nullptr);
    } catch (NullPointerException &e) {
        std::cout << e.what() << " - " << e.desc << std::endl;
    }

    delete c;
    delete d;
    return 0;
}