#ifndef BIT_ELEMENT_HPP
#define BIT_ELEMENT_HPP

#include <memory>

#include "../Constants/Constants.hpp"

namespace network {
class BitElement {
 public:
  BitElement(char* mRef, const size_t mBitOff);

  virtual ~BitElement() = default;

  bool get() const;
  void set(bool b);

  // Operators
  operator bool() const;
  BitElement& operator=(bool b);
  BitElement& operator=(const BitElement& be);

 private:
  char* mRef;
  const size_t mBitOff;
};
}  // namespace network

#endif