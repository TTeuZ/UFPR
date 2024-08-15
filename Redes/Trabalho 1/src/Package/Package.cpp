#include "Package.hpp"

#include <iostream>

namespace network {
Package::Package(uint8_t initMarker, uint8_t dataSize, uint8_t sequence, PackageTypeEnum type, const uint8_t* data)
    : initMarker{initMarker}, type{type} {
  this->setDataSize(dataSize);
  this->setSequence(sequence);
  std::memcpy(this->data, data, this->dataSize);

  this->crc = this->calcCrc();
  this->size = (4 * BITS_IN_BYTE) + (this->dataSize * BITS_IN_BYTE);
}

Package::Package(uint8_t initMarker, uint8_t dataSize, uint8_t sequence, PackageTypeEnum type)
    : initMarker{initMarker}, type{type} {
  this->setDataSize(dataSize);
  this->setSequence(sequence);
  std::memset(this->data, 0, this->dataSize);

  this->crc = this->calcCrc();
  this->size = (4 * BITS_IN_BYTE) + (this->dataSize * BITS_IN_BYTE);
}

Package::Package(const char* const buffer, size_t bytes) {
  size_t count{3}, final_len{0};
  char temp[bytes];

  for (size_t i = 0; i < bytes; ++i) {
    if (buffer[i] == (char)Constants::VLAN_BYTE_ONE || buffer[i] == (char)Constants::VLAN_BYTE_TWO)
      temp[final_len++] = buffer[i++];
    else
      temp[final_len++] = buffer[i];
  }

  this->initMarker = temp[0];
  this->dataSize = (temp[1] >> 2) & 0x3F;
  this->sequence = ((temp[1] & 0x03) << 3) | ((temp[2] & 0xE0) >> 5);
  this->type = static_cast<PackageTypeEnum>(temp[2] & 0x1F);
  for (size_t i = 0; i < this->dataSize; ++i) this->data[i] = temp[count++];
  this->crc = temp[count];
  this->size = final_len * BITS_IN_BYTE;
}

void Package::setDataSize(uint8_t dataSize) { this->dataSize = dataSize > 63 ? 63 : dataSize; }

void Package::setSequence(uint8_t sequence) { this->sequence = sequence > 31 ? 31 : sequence; }

BitArray Package::getRawPackage() {
  size_t size = this->size < Constants::MIN_PACKAGE_SIZE_IN_BITS ? Constants::MIN_PACKAGE_SIZE_IN_BITS : this->size;

  BitArray bits{size};
  this->fillUpRawArray(bits, true);

  for (size_t i = 0; i < bits.sizeBytes(); ++i) {
    if (bits.getData()[i] == (char)Constants::VLAN_BYTE_ONE || bits.getData()[i] == (char)Constants::VLAN_BYTE_TWO) {
      bits.insert(Constants::ESCAPE, i + 1);
      ++i;
    }
  }

  return bits;
}

uint16_t Package::getSize() const { return this->size; }

uint8_t Package::getDataSize() const { return this->dataSize; }

PackageTypeEnum Package::getType() const { return this->type; }

uint8_t Package::getSequence() const { return this->sequence; }

const uint8_t* Package::getData() const { return this->data; }

bool Package::checkCrc() {
  uint8_t tempCrc{this->calcCrc()};
  return tempCrc == this->crc;
}

uint8_t Package::calcCrc() {
  size_t bits_qty = (DATA_SIZE + SEQUENCE_SIZE + TYPE_SIZE + (this->dataSize * BITS_IN_BYTE));
  BitArray bits{bits_qty};

  this->fillUpRawArray(bits, false);

  uint8_t crcValue = 0x00;
  for (size_t i = 0; i < bits.size(); ++i) {
    crcValue ^= (bits[i] ? 1 : 0);
    for (size_t i = 0; i < BITS_IN_BYTE; ++i) {
      if (crcValue & 0x80)
        crcValue = (crcValue << 1) ^ Constants::CRC_POLYNOMIAL;
      else
        crcValue <<= 1;
    }
  }

  return crcValue;
}

void Package::fillUpRawArray(BitArray bits, bool full) {
  size_t count{0};

  if (full)
    for (size_t i = 0; i < BITS_IN_BYTE; ++i) bits[count++] = (this->initMarker >> (BITS_IN_BYTE - 1 - i)) & 1;

  for (size_t i = 0; i < DATA_SIZE; ++i) bits[count++] = (this->dataSize >> (DATA_SIZE - 1 - i)) & 1;
  for (size_t i = 0; i < SEQUENCE_SIZE; ++i) bits[count++] = (this->sequence >> (SEQUENCE_SIZE - 1 - i)) & 1;
  for (size_t i = 0; i < TYPE_SIZE; ++i) bits[count++] = (static_cast<uint8_t>(this->type) >> (TYPE_SIZE - 1 - i)) & 1;
  for (size_t i = 0; i < this->dataSize; ++i)
    for (size_t j = 0; j < BITS_IN_BYTE; ++j) bits[count++] = (this->data[i] >> (BITS_IN_BYTE - 1 - j)) & 1;

  if (full)
    for (size_t i = 0; i < BITS_IN_BYTE; ++i) bits[count++] = (this->crc >> (BITS_IN_BYTE - 1 - i)) & 1;
}

void Package::dummy() {
  std::cout << this->initMarker << std::endl;
  std::cout << (int)this->dataSize << std::endl;
  std::cout << (int)this->sequence << std::endl;
  std::cout << (int)this->type << std::endl;
  for (size_t i = 0; i < this->dataSize; ++i) std::cout << this->data[i];
  std::cout << std::endl;
  std::cout << (int)this->crc << std::endl;

  BitArray bits{this->size};
  this->fillUpRawArray(bits, true);

  for (size_t i = 0; i < bits.size(); ++i) {
    std::cout << bits[i];
    if (i != 0 && ((i + 1) % 8) == 0) std::cout << " ";
  }
  std::cout << std::endl;
}
}  // namespace network
