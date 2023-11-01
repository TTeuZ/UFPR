#include "CPF.hpp"

#include "CPFInvalidoException.hpp"

namespace ufpr {

CPF::CPF(const uint64_t numero) { this->setNumero(numero); }

uint64_t CPF::getNumero() const { return this->numero; }

void CPF::setNumero(const uint64_t numero) {
    if (!validarCPF(numero)) throw CPFInvalidoException{numero};
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

std::ostream& operator<<(std::ostream& stream, const CPF& cpf) {}
}  // namespace ufpr