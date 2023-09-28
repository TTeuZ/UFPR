#include <iostream>
#include <list>
#include <string>

#include "./Aluno/Aluno.hpp"
#include "./Console/Console.hpp"
#include "./ConteudoMinistrado/ConteudoMinistrado.hpp"
#include "./Curso/Curso.hpp"
#include "./Disciplina/Disciplina.hpp"
#include "./Pessoa/Pessoa.hpp"
#include "./Professor/Professor.hpp"
#include "./ProfessorAdjunto/ProfessorAdjunto.hpp"
#include "./SalaAula/SalaAula.hpp"

int main() {
    Curso bcc{"Ciência da Computação", (char)1111, (char)3600};

    SalaAula sala{"Lab Info 1", 20};
    SalaAula sala2{"Lab Info 2", 20};

    Professor prof1{"João", 11111111111, 40, 60};
    Disciplina dis1{bcc, "Orientacao a Objetos", &prof1, 60, &sala};

    Professor prof2{"Maria", 22222222222, 30, 70};
    Disciplina dis2{bcc, "Sistemas Operacionais", &prof2, 60, &sala2};

    dis1.adicionaConteudo("Ponteiros", 4);
    dis1.adicionaConteudo("Referencias", 4);
    dis2.adicionaConteudo("Strings", 4);
    dis2.adicionaConteudo("Floats", 4);

    Aluno aluno1{"Leo", 22222222222, 20203945, 0.9};
    Aluno aluno2{"Joao", 22222222222, 20203946, 0.9};
    dis1.adicionarAluno(&aluno1);
    dis1.adicionarAluno(&aluno2);

    Aluno aluno3{"Nina", 22222222222, 20203947, 0.9};
    Aluno aluno4{"Lawrence", 22222222222, 20203948, 0.9};
    dis2.adicionarAluno(&aluno3);
    dis2.adicionarAluno(&aluno4);

    Console::imprimirDadosDisciplina(dis1);

    std::cout << "-------------------------------------------\n" << std::endl;

    Console::imprimirDadosDisciplina(dis2);

    std::cout << "-------------------------------------------\n" << std::endl;
    std::cout << "Removendo conteudos\n\n";

    dis1.removerConteudoMinistrado(1);
    dis2.removerConteudoMinistrado(3);

    std::cout << "-------------------------------------------\n" << std::endl;

    Console::imprimirDadosDisciplina(dis1);

    std::cout << "-------------------------------------------\n" << std::endl;

    Console::imprimirDadosDisciplina(dis2);

    return 0;
}