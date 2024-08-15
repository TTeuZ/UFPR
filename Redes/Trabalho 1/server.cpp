#include <iostream>

#include "enums/PackageTypeEnum.hpp"
#include "src/ArgParser/ArgParser.hpp"
#include "src/Connection/ServerDownloadConnection.hpp"
#include "src/Connection/ServerListConnection.hpp"
#include "src/Constants/Constants.hpp"
#include "src/Package/Package.hpp"
#include "src/RawSocket/RawSocket.hpp"

int main(int argc, char** argv) {
  bool loopback = network::ArgParser::parseArguments(argc, argv);
  network::RawSocket* rawSocket{new network::RawSocket{loopback}};
  network::Package package;

  while (true) {
    rawSocket->recvPackage(package);

    if (package.checkCrc()) {
      switch (package.getType()) {
        case network::PackageTypeEnum::LIST: {
          network::ServerListConnection connection{rawSocket};
          connection.run();

          break;
        }
        case network::PackageTypeEnum::DOWNLOAD: {
          std::string videoName;
          for (size_t i = 0; i < package.getDataSize(); ++i)
            videoName.append(1, static_cast<char>(package.getData()[i]));

          network::ServerDownloadConnection connection{rawSocket, videoName};
          connection.run();

          break;
        }
        default: {
          // Cleaning buffer loopback
          break;
        }
      }
    } else {
      network::Package nack{network::Constants::INIT_MARKER, 0, 0, network::PackageTypeEnum::NACK};
      rawSocket->sendPackage(nack);
    }
  }

  delete rawSocket;
}