#include "BitArray.hpp"

namespace network {
BitArray::BitArray(const size_t bits) : mTotalBits{bits} {
  if (bits == 0) return;
  this->mArr = std::make_shared<std::vector<char>>(1 + ((bits - 1) / BITS_IN_BYTE));
  std::memset(this->mArr.get()->data(), 0, (1 + ((bits - 1) / BITS_IN_BYTE)));
}

size_t BitArray::size() const { return this->mTotalBits; }

size_t BitArray::sizeBytes() const { return 1 + ((this->mTotalBits - 1) / BITS_IN_BYTE); }

char* BitArray::getData() const { return static_cast<char*>(this->mArr.get()->data()); }

void BitArray::insert(char byte, size_t index) {
  std::vector<char>::iterator it{(*this->mArr).begin() + index};
  (*this->mArr).insert(it, byte);

  this->mTotalBits += BITS_IN_BYTE;
}

BitElement BitArray::operator[](size_t bit) const {
  if (bit >= this->mTotalBits) return {nullptr, 0};
  return BitElement{this->mArr.get()->data(), bit};
}
}  // namespace network
