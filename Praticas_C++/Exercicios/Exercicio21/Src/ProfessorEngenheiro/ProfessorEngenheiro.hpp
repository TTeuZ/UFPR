
#ifndef PROFESSOR_ENGENHEIRO_HPP
#define PROFESSOR_ENGENHEIRO_HPP

#include <cstdint>
#include <string>

#include "../Engenheiro/Engenheiro.hpp"
#include "../Professor/Professor.hpp"
#include "../CPF/CPF.hpp"

namespace ufpr {
class ProfessorEngenheiro : public Professor, public Engenheiro {
   public:
    // Constructor
    ProfessorEngenheiro(const std::string& nome, const CPF& cpf, const uint16_t valorHora, const uint8_t cargaHoraria,
                        const uint16_t numeroCrea);

    // Destructor
    virtual ~ProfessorEngenheiro() = default;

    // Functions
    virtual uint32_t getSalario() const override;
};
}  // namespace ufpr
#endif
