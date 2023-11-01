#ifndef CPF_HPP
#define CPF_HPP

#include <cstdint>

namespace ufpr {
class CPF {
    friend std::ostream& operator<<(std::ostream& stream, const CPF& cpf);

   public:
    CPF(const uint64_t numero);
    virtual ~CPF() = default;
    uint64_t getNumero() const;
    void setNumero(const uint64_t numero);

    const CPF& operator=(const CPF& outro);
    const CPF& operator=(const uint64_t numero);
    bool operator==(const CPF& outro) const;
    bool operator!=(const CPF& outro) const;
    bool operator<(const CPF& outro) const;
    bool operator>(const CPF& outro) const;
    bool operator<=(const CPF& outro) const;
    bool operator>=(const CPF& outro) const;

   private:
    bool validarCPF(uint64_t cpfTeste) const;
    uint64_t numero;
};
}  // namespace ufpr
#endif