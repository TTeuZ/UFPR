#include "ProfessorEngenheiro.hpp"

namespace ufpr {
// Constructor
ProfessorEngenheiro::ProfessorEngenheiro(const std::string& nome,
                                         const uint64_t cpf,
                                         const uint16_t valorHora,
                                         const uint8_t cargaHoraria,
                                         const uint16_t numeroCrea)
    : Pessoa{nome, cpf},
      Professor{nome, cpf, valorHora, cargaHoraria},
      Engenheiro{nome, cpf, numeroCrea} {}

// Functions
uint32_t ProfessorEngenheiro::getSalario() const {
    return this->Professor::getSalario() + this->Engenheiro::getSalario();
}
}