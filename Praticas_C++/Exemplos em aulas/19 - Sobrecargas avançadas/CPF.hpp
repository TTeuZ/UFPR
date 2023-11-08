#ifndef CPF_HPP
#define CPF_HPP

#include <cstdint>
#include <iostream>

namespace ufpr {
class CPF {
    friend std::ostream& operator<<(std::ostream& stream, const CPF& cpf);

   public:
    CPF(const uint64_t numero);
    virtual ~CPF() = default;
    uint64_t getNumero() const;
    void setNumero(const unsigned long numero);

    bool operator==(const CPF& outro) const;
    bool operator!=(const CPF& outro) const;

    bool operator<(const CPF& outro) const;
    bool operator>(const CPF& outro) const;
    bool operator<=(const CPF& outro) const;
    bool operator>=(const CPF& outro) const;

    const CPF& operator=(const CPF& outro);
    const CPF& operator=(const unsigned long numero);

   private:
    bool validarCPF(uint64_t cpfTeste) const;
    uint64_t numero;
};
}  // namespace ufpr
#endif