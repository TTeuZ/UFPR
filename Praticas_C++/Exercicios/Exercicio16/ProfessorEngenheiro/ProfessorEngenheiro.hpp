
#ifndef PROFESSOR_ENGENHEIRO_HPP
#define PROFESSOR_ENGENHEIRO_HPP

#include <cstdint>
#include <string>

#include "../Engenheiro/Engenheiro.hpp"
#include "../Professor/Professor.hpp"

class ProfessorEngenheiro : public Professor, public Engenheiro {
   public:
    // Constructor
    ProfessorEngenheiro(const std::string& nome, const uint64_t cpf,
                        const uint16_t valorHora, const uint8_t cargaHoraria,
                        const uint16_t numeroCrea);

    // Destructor
    virtual ~ProfessorEngenheiro() = default;

    // Functions
    virtual uint32_t getSalario() const override;
};
#endif
