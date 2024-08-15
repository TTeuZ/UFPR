#ifndef TIMEOUT_EXCEPTION_HPP
#define TIMEOUT_EXCEPTION_HPP

#include <stdexcept>

namespace exceptions {
class TimeoutException : public std::runtime_error {
 public:
  explicit TimeoutException(const std::string& desc);

  virtual ~TimeoutException() = default;

  const std::string desc;
};
}  // namespace exceptions

#endif