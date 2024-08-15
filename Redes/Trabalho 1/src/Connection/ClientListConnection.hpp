#ifndef CLIENT_LIST_CONNECTION_HPP
#define CLIENT_LIST_CONNECTION_HPP

#include "../../enums/PackageTypeEnum.hpp"
#include "../../exceptions/TimeoutException/TimeoutException.hpp"
#include "../Constants/Constants.hpp"
#include "../Package/Package.hpp"
#include "../RawSocket/RawSocket.hpp"
#include "Connection.hpp"

namespace network {
class ClientListConnection : public Connection {
 public:
  ClientListConnection(RawSocket* rawSocket);

  virtual ~ClientListConnection() = default;

  void run() override;
};
}  // namespace network

#endif