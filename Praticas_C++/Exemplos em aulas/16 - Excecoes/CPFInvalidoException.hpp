#ifndef CPF_INVALIDO_EXCEPTION
#define CPF_INVALIDO_EXCEPTION

#include <stdexcept>

class CPFInvalidoException : public std::runtime_error {
   public:
    const uint64_t cpf;
    CPFInvalidoException(const uint64_t cpf);
    virtual ~CPFInvalidoException() = default;
};
#endif
