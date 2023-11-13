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
    ufpr::CPF cpf1{11111111111};
    ufpr::CPF cpf2{22222222222};
    ufpr::CPF cpf3{33333333333};

    std::string cpf_string{static_cast<std::string>(cpf1)};
    unsigned long int cpf_int{static_cast<unsigned long int>(cpf2)};

    std::cout << "CPF: " << cpf_string << std::endl;
    std::cout << "CPF: " << cpf_int << std::endl;
    std::cout << "CPF: " << cpf3 << std::endl;

    return 0;
}