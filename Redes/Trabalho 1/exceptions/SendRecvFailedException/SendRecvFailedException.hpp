#ifndef SEND_FAILED_EXCEPTION_HPP
#define SEND_FAILED_EXCEPTION_HPP

#include <stdexcept>

namespace exceptions {
class SendRecvFailedException : public std::runtime_error {
 public:
  explicit SendRecvFailedException(const std::string& desc);

  virtual ~SendRecvFailedException() = default;

  const std::string desc;
};
}  // namespace exceptions

#endif