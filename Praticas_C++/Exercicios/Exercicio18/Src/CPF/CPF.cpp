#include "CPF.hpp"

#include <iomanip>
#include <stdexcept>

#include "../../Exceptions/CPFInvalidoException/CPFInvalidoException.hpp"

namespace ufpr {

CPF::CPF(const uint64_t numero) { this->setNumero(numero); }

uint64_t CPF::getNumero() const { return this->numero; }

void CPF::setNumero(const uint64_t numero) {
    if (!validarCPF(numero)) throw exceptions::CPFInvalidoException{numero};
    this->numero = numero;
}

bool CPF::validarCPF(uint64_t cpfTeste) const {
    unsigned int somatorioValidaUltimo;
    unsigned int modulo;
    unsigned int somatorioValidaPenultimo{0};
    unsigned int ultimo{(unsigned int)(cpfTeste % 10)};
    cpfTeste = cpfTeste / 10;
    unsigned int penultimo{(unsigned int)(cpfTeste % 10)};
    cpfTeste = cpfTeste / 10;

    somatorioValidaUltimo = penultimo * 2;
    for (int i{2}; i <= 11; i++) {
        modulo = cpfTeste % 10;
        cpfTeste = cpfTeste / 10;
        somatorioValidaPenultimo += modulo * i;
        somatorioValidaUltimo += modulo * (i + 1);
    }
    modulo = somatorioValidaPenultimo % 11;
    if (modulo < 2) {
        if (penultimo != 0) return false;  // cpf invalido
    } else {
        if (penultimo != 11 - modulo) return false;  // cpf invalido
    }
    modulo = somatorioValidaUltimo % 11;
    if (modulo < 2) {
        if (!ultimo) return false;  // cpf invalido
    } else {
        if (ultimo != 11 - modulo) return false;  // cpf invalido
    }
    return true;  // cpf valido
}

const CPF& CPF::operator=(const CPF& outro) {
    if (&outro != this) this->numero = outro.numero;
    return *this;
}

const CPF& CPF::operator=(const uint64_t numero) {
    this->setNumero(numero);
    return *this;
}

bool CPF::operator==(const CPF& outro) const {
    return this->numero == outro.numero;
}

bool CPF::operator!=(const CPF& outro) const { return !(*this == outro); }

bool CPF::operator<(const CPF& outro) const {
    return this->numero < outro.numero;
}

bool CPF::operator>(const CPF& outro) const { return (outro < *this); }

bool CPF::operator<=(const CPF& outro) const { return !(*this > outro); }

bool CPF::operator>=(const CPF& outro) const { return !(*this < outro); }

unsigned short CPF::operator[](const int idx) const {
    if (idx < 0 || idx >= 11)
        throw std::out_of_range{"Posição indicada fora dos limites"};

    uint64_t temp = this->numero;
    uint8_t result{0};
    for (int i{0}; i < 11 - idx; ++i) {
        result = temp % 10;
        temp = temp / 10;
    }

    return result;
}

std::ostream& operator<<(std::ostream& stream, const CPF& cpf) {
    unsigned int verificador{(unsigned int)(cpf.numero % 100)};
    uint64_t prim{cpf.numero / 100};
    unsigned int ter{(unsigned int)(prim % 1000)};
    prim /= 1000;
    unsigned int seg{(unsigned int)(prim % 1000)};
    prim /= 1000;

    stream << std::setw(3) << std::setfill('0');
    stream << prim << '.' << seg << '.' << ter << '-' << verificador;
    return stream;  // permitir cout << a << b << c;
}

std::istream& operator>>(std::istream& stream, CPF& cpf) {
    uint64_t numero;
    stream >> numero;

    cpf.setNumero(numero);
    return stream;
}
}  // namespace ufpr
