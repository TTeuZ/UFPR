#ifndef SOCKET_CREATE_EXCEPTION_HPP
#define SOCKET_CREATE_EXCEPTION_HPP

#include <stdexcept>

namespace exceptions {
class SocketCreateException : public std::runtime_error {
 public:
  explicit SocketCreateException(const std::string& desc);

  virtual ~SocketCreateException() = default;

  const std::string desc;
};
}  // namespace exceptions

#endif