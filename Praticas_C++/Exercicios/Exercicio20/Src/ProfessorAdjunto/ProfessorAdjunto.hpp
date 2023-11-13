#ifndef PROFESSOR_ADJUNTO_HPP
#define PROFESSOR_ADJUNTO_HPP

#include <cstdint>
#include <string>

#include "../Professor/Professor.hpp"
#include "../CPF/CPF.hpp"

namespace ufpr {
class ProfessorAdjunto : public Professor {
   public:
    // Constructors
    ProfessorAdjunto(const std::string& nome, const CPF& cpf, const uint16_t valorHora, const uint8_t cargaHoraria);

    // Destructor
    virtual ~ProfessorAdjunto() = default;

    // Getters
    const std::string& getLinhaPesquisa() const;

    // Setters
    void setLinhaPesquisa(const std::string& linhaPesquisa);

    // functions
    virtual uint32_t getSalario() const override;

   private:
    std::string linhaPesquisa;
};
}  // namespace ufpr

#endif