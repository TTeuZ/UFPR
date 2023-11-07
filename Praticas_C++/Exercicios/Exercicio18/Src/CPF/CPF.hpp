#ifndef CPF_HPP
#define CPF_HPP

#include <cstdint>
#include <iostream>

namespace ufpr {
class CPF {
    friend std::ostream& operator<<(std::ostream& stream, const CPF& cpf);
    friend std::istream& operator>>(std::istream& stream, CPF& cpf);

   public:
    // Constructors
    CPF(const uint64_t numero);

    // Destructor
    virtual ~CPF() = default;

    // Getters
    uint64_t getNumero() const;

    // Setters
    void setNumero(const uint64_t numero);

    // Operators
    const CPF& operator=(const CPF& outro);
    const CPF& operator=(const uint64_t numero);
    bool operator==(const CPF& outro) const;
    bool operator!=(const CPF& outro) const;
    bool operator<(const CPF& outro) const;
    bool operator>(const CPF& outro) const;
    bool operator<=(const CPF& outro) const;
    bool operator>=(const CPF& outro) const;
    unsigned short operator[](const int idx) const;

   private:
    bool validarCPF(uint64_t cpfTeste) const;
    uint64_t numero;
};
}  // namespace ufpr
#endif