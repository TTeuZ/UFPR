#ifndef NULL_POINTER_EXCEPTION_HPP
#define NULL_POINTER_EXCEPTION_HPP

#include <stdexcept>

class NullPointerException : public std::runtime_error {
   public:
    // Constructor
    NullPointerException(const std::string& desc);

    // Destructor
    virtual ~NullPointerException() = default;

    const std::string& desc;
};

#endif