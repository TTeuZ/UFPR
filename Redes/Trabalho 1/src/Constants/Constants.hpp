#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>

#define MAX_DATA_SIZE 63
#define DATA_SIZE 6
#define SEQUENCE_SIZE 5
#define TYPE_SIZE 5
#define BITS_IN_BYTE 8

#define WINDOW_SIZE 5

namespace network {
class Constants {
 public:
  Constants() = delete;

  virtual ~Constants() = default;

  const static char* LOOPBACK_INTERFACE_NAME;
  const static char* ETHERNET_INTERFACE_NAME;

  const static int TIMEOUT;
  const static int TIMEOUT_RETRY;
  const static int STATUS_OK;
  const static int STATUS_RETRY;

  const static uint8_t INIT_MARKER;
  const static uint8_t CRC_POLYNOMIAL;

  const static uint8_t MAX_SEQUENCE_SIZE;

  const static uint8_t MAX_PACKAGE_SIZE;
  const static uint8_t MIN_PACKAGE_SIZE_IN_BITS;

  const static uint8_t VLAN_BYTE_ONE;
  const static uint8_t VLAN_BYTE_TWO;
  const static uint8_t ESCAPE;

  const static char* VIDEOS_PATH;
  const static char* DOWNLOADS_PATH;
};
}  // namespace network

#endif