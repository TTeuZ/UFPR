#ifndef PROFESSOR_ADJUNTO_HPP
#define PROFESSOR_ADJUNTO_HPP

#include "Professor.hpp"

namespace ufpr{
class ProfessorAdjunto : public Professor{
    public:
        ProfessorAdjunto(const std::string& nome, const unsigned long cpf,
                const unsigned int salario, const unsigned short cargaHoraria);
        ProfessorAdjunto(const std::string& nome, const CPF& cpf,
                const unsigned int salario, const unsigned short cargaHoraria);

        virtual ~ProfessorAdjunto();

        const std::string& getLinhaPesquisa() const;
        void setLinhaPesquisa(const std::string& linhaPesquisa);

        virtual unsigned int getSalario() const override;
    private:
        std::string linhaPesquisa;
};
}
#endif