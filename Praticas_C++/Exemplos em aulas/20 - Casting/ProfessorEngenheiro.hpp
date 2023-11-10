#ifndef PROFESSOR_ENGENHEIRO_HPP
#define PROFESSOR_ENGENHEIRO_HPP

#include "string"

#include "Professor.hpp"
#include "Engenheiro.hpp"

namespace ufpr{
class ProfessorEngenheiro : public Professor, public Engenheiro{
    public:
        ProfessorEngenheiro(const std::string& nome, const unsigned long cpf,
                const unsigned int valorHora, const unsigned short cargaHoraria,
                const unsigned int numeroCrea);

        ProfessorEngenheiro(const std::string& nome, const CPF& cpf,
                const unsigned int valorHora, const unsigned short cargaHoraria,
                const unsigned int numeroCrea);

        virtual ~ProfessorEngenheiro();

        virtual unsigned int getSalario() const override;
};
}
#endif