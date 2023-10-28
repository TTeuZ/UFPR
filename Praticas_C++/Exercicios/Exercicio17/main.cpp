#include <iostream>
#include <stdexcept>

#include "./Enums/EnumTipoDisciplina.hpp"
#include "./Exceptions/CPFInvalidoException/CPFInvalidoException.hpp"
#include "./Exceptions/NaoPositivoException/NaoPositivoException.hpp"
#include "./Exceptions/NullPointerException/NullPointerException.hpp"
#include "./Src/Aluno/Aluno.hpp"
#include "./Src/Console/Console.hpp"
#include "./Src/ConteudoMinistrado/ConteudoMinistrado.hpp"
#include "./Src/Curso/Curso.hpp"
#include "./Src/Disciplina/Disciplina.hpp"
#include "./Src/Engenheiro/Engenheiro.hpp"
#include "./Src/Pessoa/Pessoa.hpp"
#include "./Src/Professor/Professor.hpp"
#include "./Src/ProfessorAdjunto/ProfessorAdjunto.hpp"
#include "./Src/ProfessorEngenheiro/ProfessorEngenheiro.hpp"
#include "./Src/SalaAula/SalaAula.hpp"

int main() {
    ufpr::Curso *c;
    ufpr::Disciplina *d;
    try {
        c = new ufpr::Curso{"Batata", (unsigned char)2023, (unsigned char)3000};
        d = new ufpr::Disciplina{*c, "Pão de batata 1", 60,
                                 ufpr::enums::EnumTipoDisciplina::MANDATORIA};
    } catch (std::bad_alloc &e) {
        std::cout << "Erro de alocação - " << e.what() << std::endl;
        return 1;
    } catch (ufpr::exceptions::NaoPositivoException &e) {
        std::cout << e.what() << " - " << e.desc << std::endl;
        return 1;
    } catch (std::invalid_argument &e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    delete c;
    delete d;
    return 0;
}