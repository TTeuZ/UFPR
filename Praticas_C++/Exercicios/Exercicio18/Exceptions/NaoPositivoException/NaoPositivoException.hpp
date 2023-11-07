#ifndef NAO_POSITIVO_EXCEPTION_HPP
#define NAO_POSITIVO_EXCEPTION_HPP

#include <stdexcept>

namespace ufpr {
namespace exceptions {

class NaoPositivoException : public std::invalid_argument {
   public:
    // Constructor
    NaoPositivoException(const std::string& desc);

    // Destructor
    virtual ~NaoPositivoException() = default;

    const std::string desc;
};

}  // namespace exceptions
}  // namespace ufpr

#endif