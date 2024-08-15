#ifndef BIT_ARRAY_HPP
#define BIT_ARRAY_HPP

#include <cstring>
#include <memory>
#include <vector>

#include "../Constants/Constants.hpp"
#include "BitElement.hpp"

namespace network {
class BitArray {
 public:
  BitArray(const size_t bits);

  virtual ~BitArray() = default;

  size_t size() const;
  size_t sizeBytes() const;

  char* getData() const;

  void insert(char byte, size_t index);

  // Operators
  BitElement operator[](size_t bit) const;

 private:
  std::shared_ptr<std::vector<char>> mArr;
  size_t mTotalBits;
};
}  // namespace network

#endif