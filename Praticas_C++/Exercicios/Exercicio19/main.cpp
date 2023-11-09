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

int main() {
    ufpr::Curso *c = new ufpr::Curso{"Batata", (unsigned char)2023, (unsigned char)3000};
    ufpr::Disciplina *d1 = new ufpr::Disciplina{*c, "Pão de batata 1", 60, ufpr::enums::EnumTipoDisciplina::MANDATORIA};

    d1->adicionaConteudo("teste1", 60);
    d1->adicionaConteudo("teste2", 60);
    d1->adicionaConteudo("teste3", 60);

    ufpr::Disciplina d2{*d1};

    delete d1;

    std::list<ufpr::ConteudoMinistrado *>::const_iterator it{d2.getConteudos().begin()};
    for (; it != d2.getConteudos().end(); ++it) std::cout << (*it)->getDescricao() << std::endl;

    return 0;
}