#include "Constants.hpp"

namespace network {
const char* Constants::LOOPBACK_INTERFACE_NAME{"lo"};
const char* Constants::ETHERNET_INTERFACE_NAME{"enp0s31f6"};

const int Constants::TIMEOUT{10};
const int Constants::TIMEOUT_RETRY{5};
const int Constants::STATUS_OK{0};
const int Constants::STATUS_RETRY{-1};

const uint8_t Constants::INIT_MARKER{126};
const uint8_t Constants::CRC_POLYNOMIAL{0x07};

const uint8_t Constants::MAX_SEQUENCE_SIZE{32};

const uint8_t Constants::MAX_PACKAGE_SIZE{static_cast<uint8_t>(67)};
const uint8_t Constants::MIN_PACKAGE_SIZE_IN_BITS{static_cast<uint8_t>(112)};

const uint8_t Constants::VLAN_BYTE_ONE{0x88};
const uint8_t Constants::VLAN_BYTE_TWO{0x81};
const uint8_t Constants::ESCAPE{0xff};

const char* Constants::VIDEOS_PATH{"./resources/videos"};
const char* Constants::DOWNLOADS_PATH{"./resources/downloads"};
}  // namespace network