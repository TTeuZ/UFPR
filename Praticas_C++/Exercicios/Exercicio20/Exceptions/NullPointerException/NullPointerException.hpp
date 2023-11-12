#ifndef NULL_POINTER_EXCEPTION_HPP
#define NULL_POINTER_EXCEPTION_HPP

#include <stdexcept>

namespace ufpr {
namespace exceptions {

class NullPointerException : public std::runtime_error {
   public:
    // Constructor
    explicit NullPointerException(const std::string& desc);

    // Destructor
    virtual ~NullPointerException() = default;

    const std::string desc;
};

}  // namespace exceptions
}  // namespace ufpr

#endif