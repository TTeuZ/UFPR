#ifndef RAWSOCKET_HPP
#define RAWSOCKET_HPP

#include <arpa/inet.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <netinet/if_ether.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netpacket/packet.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

#include <chrono>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

#include "../../exceptions/SendRecvFailedException/SendRecvFailedException.hpp"
#include "../../exceptions/SocketCreateException/SocketCreateException.hpp"
#include "../../exceptions/TimeoutException/TimeoutException.hpp"
#include "../BitArray/BitArray.hpp"
#include "../Constants/Constants.hpp"
#include "../Package/Package.hpp"

namespace network {
class RawSocket {
 public:
  RawSocket(const bool loopback);

  virtual ~RawSocket();

  void sendPackage(Package& package);
  int recvPackage(Package& package);

  void activeTimeout();
  void deactiveTimeout();

 private:
  bool can_write();
  bool can_read();

  time_t timestamp();

  bool loopback;
  int socket_id;
  struct sockaddr_ll address;
  struct packet_mreq mr;

  struct timeval timeout;
  int sendTimes;
  int recvTimes;
  bool timeoutActivated;

  // Loopback only
  int skipNext;
};
}  // namespace network

#endif