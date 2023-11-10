#ifndef CPF_HPP
#define CPF_HPP

#include <iostream>

namespace ufpr {
class CPF {
    friend std::ostream& operator<<(std::ostream& stream, const CPF& cpf);
    friend std::istream& operator>>(std::istream& stream, CPF& cpf);

   public:
    CPF() = default;
    explicit CPF(const unsigned long numero);
    virtual ~CPF() = default;
    unsigned long getNumero() const;
    void setNumero(const unsigned long numero);

    bool operator==(const CPF& outro) const;
    bool operator!=(const CPF& outro) const;

    bool operator<(const CPF& outro) const;
    bool operator>(const CPF& outro) const;
    bool operator<=(const CPF& outro) const;
    bool operator>=(const CPF& outro) const;

    const CPF& operator=(const CPF& outro);
    const CPF& operator=(const unsigned long numero);

    unsigned short operator[](short int idx) const;
    unsigned long operator()(short int inicio, short int tam) const;

    explicit operator uint64_t() const;

   private:
    bool validarCPF(unsigned long cpfTeste) const;
    unsigned long numero;
};
}  // namespace ufpr
#endif