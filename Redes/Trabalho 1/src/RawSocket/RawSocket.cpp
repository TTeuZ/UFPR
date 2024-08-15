#include "RawSocket.hpp"

namespace network {
RawSocket::RawSocket(const bool loopback)
    : loopback{loopback}, sendTimes{0}, recvTimes{0}, timeoutActivated{false}, skipNext{0} {
  const char* interface_name = loopback ? Constants::LOOPBACK_INTERFACE_NAME : Constants::ETHERNET_INTERFACE_NAME;

  this->socket_id = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
  if (this->socket_id < 0)
    throw exceptions::SocketCreateException("Fail in create socket - Please check if you have root permissions!");

  int ifindex = if_nametoindex(interface_name);

  this->address = {0};
  this->address.sll_family = AF_PACKET;
  this->address.sll_protocol = htons(ETH_P_ALL);
  this->address.sll_ifindex = ifindex;

  if (bind(socket_id, (struct sockaddr*)&this->address, sizeof(this->address)) == -1)
    throw exceptions::SocketCreateException("Error binding socket!");

  this->mr = {0};
  this->mr.mr_ifindex = ifindex;
  this->mr.mr_type = PACKET_MR_PROMISC;

  if (setsockopt(this->socket_id, SOL_PACKET, PACKET_ADD_MEMBERSHIP, &this->mr, sizeof(this->mr)) == -1)
    throw exceptions::SocketCreateException("Error executing setsockopt!");

  this->timeout.tv_sec = Constants::TIMEOUT;
  this->timeout.tv_usec = 0;
  if (setsockopt(this->socket_id, SOL_SOCKET, SO_SNDTIMEO, (char*)&this->timeout, sizeof(this->timeout)) < 0)
    throw exceptions::SocketCreateException("Error activating timeout for send!");

  if (setsockopt(this->socket_id, SOL_SOCKET, SO_RCVTIMEO, (char*)&this->timeout, sizeof(this->timeout)) < 0)
    throw exceptions::SocketCreateException("Error activating timeout for recv!");
}

RawSocket::~RawSocket() { close(this->socket_id); }

void RawSocket::sendPackage(Package& package) {
  BitArray bits{package.getRawPackage()};
  bool sent{false};

  if (this->loopback) this->skipNext++;

  while (!sent && this->sendTimes < Constants::TIMEOUT_RETRY) {
    if (this->can_write()) {
      if (write(this->socket_id, bits.getData(), bits.sizeBytes()) == -1)
        throw exceptions::SendRecvFailedException("Error sending package");

      this->sendTimes = 0;
      sent = true;
    } else
      this->sendTimes++;
  }

  if (this->sendTimes == Constants::TIMEOUT_RETRY) {
    this->sendTimes = 0;
    throw exceptions::TimeoutException("Timeout!");
  }
}

int RawSocket::recvPackage(Package& package) {
  char buffer[Constants::MAX_PACKAGE_SIZE * 2];
  ssize_t recv_len;

  time_t begin{this->timestamp()};
  do {
    if (this->can_read()) {
      if ((recv_len = read(this->socket_id, &buffer, sizeof(buffer))) == -1)
        throw exceptions::SendRecvFailedException("Error receving package");

      if (buffer[0] == Constants::INIT_MARKER) {
        if (this->loopback) {
          if (this->skipNext <= 0) {
            this->skipNext++;
            this->recvTimes = 0;
            package = Package{buffer, static_cast<size_t>(recv_len)};
            return Constants::STATUS_OK;
          } else
            this->skipNext--;
        } else {
          this->recvTimes = 0;
          package = Package{buffer, static_cast<size_t>(recv_len)};
          return Constants::STATUS_OK;
        }
      }
    }
  } while ((this->timestamp() - begin) <= Constants::TIMEOUT);

  if (this->timeoutActivated) {
    if (this->recvTimes >= Constants::TIMEOUT_RETRY) {
      this->recvTimes = 0;
      throw exceptions::TimeoutException("Timeout!");
    }

    std::cerr << "Connection Timeout - Retrying..." << std::endl;
    this->recvTimes++;
  }

  package = {};
  return Constants::STATUS_RETRY;
}

bool RawSocket::can_write() {
  fd_set write_fd;

  FD_ZERO(&write_fd);
  FD_SET(this->socket_id, &write_fd);
  int ready_fds = select(this->socket_id + 1, NULL, &write_fd, NULL, &this->timeout);
  if (ready_fds > 0 && FD_ISSET(this->socket_id, &write_fd)) return true;
  return false;
}

bool RawSocket::can_read() {
  fd_set read_fd;

  FD_ZERO(&read_fd);
  FD_SET(this->socket_id, &read_fd);
  int ready_fds = select(this->socket_id + 1, &read_fd, NULL, NULL, &this->timeout);
  if (ready_fds > 0 && FD_ISSET(this->socket_id, &read_fd)) return true;
  return false;
}

void RawSocket::activeTimeout() { this->timeoutActivated = true; }
void RawSocket::deactiveTimeout() { this->timeoutActivated = false; }

time_t RawSocket::timestamp() {
  auto now = std::chrono::system_clock::now();
  time_t seconds = std::chrono::system_clock::to_time_t(now);

  return seconds;
}
}  // namespace network