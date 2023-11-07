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
    ufpr::CPF cpf{11111111111};

    std::cout << "Informe o cpf: " << std::endl;
    std::cin >> cpf;
    std::cout << cpf << std::endl;

    int index;
    std::cout << "Informe o indice: " << std::endl;
    std::cin >> index;

    std::cout << "Valor no indice " << index << ": " << cpf[index] << std::endl;

    ufpr::Pessoa p1{"Batata1", cpf};
    ufpr::Pessoa p2{"Batata2", cpf};
    ufpr::Pessoa p3{"Batata1", cpf};

    if (p1 == p2)
        std::cout << "p1 == p2" << std::endl;
    else
        std::cout << "p1 != p2" << std::endl;

    if (p1 == p3)
        std::cout << "p1 == p3" << std::endl;
    else
        std::cout << "p1 != p3" << std::endl;

    if (p2 == p3)
        std::cout << "p2 == p3" << std::endl;
    else
        std::cout << "p2 != p3" << std::endl;

    if (p1 == p1)
        std::cout << "p1 == p1" << std::endl;
    else
        std::cout << "p1 != p1" << std::endl;

    return 0;
}