#ifndef SERVER_DOWNLOAD_CONNECTION_HPP
#define SERVER_DOWNLOAD_CONNECTION_HPP

#include <algorithm>
#include <filesystem>
#include <fstream>

#include "../../enums/PackageTypeEnum.hpp"
#include "../../exceptions/TimeoutException/TimeoutException.hpp"
#include "../Constants/Constants.hpp"
#include "../Package/Package.hpp"
#include "../RawSocket/RawSocket.hpp"
#include "Connection.hpp"

namespace network {
class ServerDownloadConnection : public Connection {
 public:
  ServerDownloadConnection(RawSocket* rawSocket, const std::string& videoName);

  virtual ~ServerDownloadConnection() = default;

  void run() override;

 private:
  std::string videoName;
};
};  // namespace network

#endif