#ifndef ENGENHEIRO_HPP
#define ENGENHEIRO_HPP

#include <cstdint>
#include <string>

#include "../Pessoa/Pessoa.hpp"

namespace ufpr {
class Engenheiro : virtual public Pessoa {
   public:
    // Constructors
    Engenheiro(const std::string& nome, const uint64_t cpf,
               const uint16_t numeroCrea);

    // Destructor
    virtual ~Engenheiro() = default;

    // Getters
    uint16_t getNumeroCrea() const;

    // Setters
    void setNumeroCrea(const uint16_t numeroCrea);

    // Functions
    virtual uint32_t getSalario() const;

   private:
    constexpr static uint32_t salarioPadrâo{9405};
    uint16_t numeroCrea;
};
}  // namespace ufpr
#endif