#include "CPFInvalidoException.hpp"

using namespace ufpr::exceptions;

CPFInvalidoException::CPFInvalidoException(const uint64_t cpf) : std::runtime_error{"CPF Invalido."}, cpf{cpf} {}
