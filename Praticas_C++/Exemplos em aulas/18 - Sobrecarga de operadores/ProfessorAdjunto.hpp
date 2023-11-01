#ifndef PROFESSOR_ADJUNTO_HPP
#define PROFESSOR_ADJUNTO_HPP

#include "Professor.hpp"

namespace ufpr{
class ProfessorAdjunto : public Professor{
    public:
        using Professor::Professor;

        virtual ~ProfessorAdjunto();

        const std::string& getLinhaPesquisa() const;
        void setLinhaPesquisa(const std::string& linhaPesquisa);

        virtual unsigned int getSalario() const override;
    private:
        std::string linhaPesquisa;
};
}
#endif