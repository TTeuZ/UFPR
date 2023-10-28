#include "CPFInvalidoException.hpp"

using namespace ufpr::exceptions;

CPFInvalidoException::CPFInvalidoException(const unsigned long cpf)
    : std::runtime_error{"CPF Invalido."}, cpf{cpf} {}
