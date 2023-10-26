#ifndef NAO_POSITIVO_EXCEPTION_HPP
#define NAO_POSITIVO_EXCEPTION_HPP

#include <stdexcept>
#include <string>

class NaoPositivoException : public std::invalid_argument {
   public:
    // Constructor
    NaoPositivoException(const std::string& desc);

    // Destructor
    virtual ~NaoPositivoException() = default;

    const std::string& desc;
};

#endif