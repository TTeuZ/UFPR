#ifndef CPF_INVALIDO_EXCEPTION
#define CPF_INVALIDO_EXCEPTION

#include <stdexcept>

class CPFInvalidoException : public std::runtime_error {
   public:
    // Constructor
    CPFInvalidoException(const uint64_t cpf);

    // Destrcutor
    virtual ~CPFInvalidoException() = default;

    const uint64_t cpf;
};
#endif
