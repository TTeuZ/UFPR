#ifndef PACKAGE_TYPE_ENUM_HPP
#define PACKAGE_TYPE_ENUM_HPP

namespace network {
enum class PackageTypeEnum {
  ACK = 0x00,
  NACK = 0x01,
  LIST = 0x0a,
  DOWNLOAD = 0x0b,
  SHOW = 0x10,
  FILE_HEADER = 0x11,
  DATA = 0x12,
  END_TX = 0x1e,
  ERROR = 0x1f
};
}

#endif