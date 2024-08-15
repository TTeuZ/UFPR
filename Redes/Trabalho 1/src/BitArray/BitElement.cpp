#include "BitElement.hpp"

namespace network {
BitElement::BitElement(char* mRef, const size_t mBitOff) : mRef{mRef}, mBitOff{mBitOff} {}

bool BitElement::get() const {
  if (!this->mRef) return false;
  const size_t off = this->mBitOff / BITS_IN_BYTE;
  const size_t bt = BITS_IN_BYTE - (this->mBitOff % BITS_IN_BYTE) - 1;
  return this->mRef[off] & (1 << bt);
}

void BitElement::set(bool b) {
  if (!this->mRef) return;
  const size_t off = this->mBitOff / BITS_IN_BYTE;
  const size_t bt = BITS_IN_BYTE - (this->mBitOff % BITS_IN_BYTE) - 1;
  this->mRef[off] = (this->mRef[off] & (~(1 << bt))) | ((uint8_t)b << bt);
}

BitElement::operator bool() const { return this->get(); }

BitElement& BitElement::operator=(bool b) {
  this->set(b);
  return *this;
}

BitElement& BitElement::operator=(const BitElement& be) {
  this->set(be.get());
  return *this;
}
}  // namespace network
