#include "ClientDownloadConnection.hpp"

namespace network {
ClientDownloadConnection::ClientDownloadConnection(RawSocket* rawSocket, const std::string& videoName)
    : Connection{rawSocket} {
  this->videoName = videoName;
};

void ClientDownloadConnection::run() {
  bool running{true};
  Package package;
  int status;

  if (this->videoName.length() > MAX_DATA_SIZE) {
    std::cout << "Nome excedeu os limites!" << std::endl;
    return;
  }

  try {
    const uint8_t* data{reinterpret_cast<const uint8_t*>(this->videoName.c_str())};
    Package initialPackage{Constants::INIT_MARKER, static_cast<uint8_t>(this->videoName.length()), 0,
                           PackageTypeEnum::DOWNLOAD, data};

    this->rawSocket->sendPackage(initialPackage);
    this->wait_ack(initialPackage);

    // Waiting header
    uintmax_t fileSize{0};
    while (running) {
      status = this->rawSocket->recvPackage(package);

      if (status == Constants::STATUS_OK) {
        if (package.checkCrc()) {
          this->lastSequence = package.getSequence();
          Package ack{Constants::INIT_MARKER, 0, this->lastSequence, PackageTypeEnum::ACK};

          if (package.getType() == PackageTypeEnum::FILE_HEADER) {
            for (size_t i = 0; i < package.getDataSize(); ++i)
              fileSize |= static_cast<uintmax_t>(package.getData()[i]) << ((7 - i) * BITS_IN_BYTE);

            this->rawSocket->sendPackage(ack);
            running = false;
          } else if (package.getType() == PackageTypeEnum::ERROR) {
            std::cout << "Arquivo inexistente!" << std::endl;
            this->rawSocket->sendPackage(ack);

            return;
          }
        } else {
          Package nack{Constants::INIT_MARKER, 0, this->lastSequence, PackageTypeEnum::NACK};
          this->rawSocket->sendPackage(nack);
        }
      }
    }

    std::cout << "\nRecebendo arquivo - " << this->videoName << std::endl;
    uintmax_t totalPackages{static_cast<uintmax_t>(std::ceil(static_cast<double>(fileSize) / MAX_DATA_SIZE))};

    // Receive packages
    bool crcFailed{false};
    size_t windowCount{0};
    uintmax_t recvPackages{0};
    std::vector<Package> packages;
    std::vector<Package> windowPackages;
    while (recvPackages < totalPackages) {
      status = this->rawSocket->recvPackage(package);

      if (status == Constants::STATUS_OK) {
        if (!package.checkCrc()) crcFailed = true;
        if (!crcFailed) windowPackages.push_back(package);
        ++windowCount;

        if ((windowCount % WINDOW_SIZE) == 0 || (recvPackages + windowCount) >= totalPackages) {
          if (!windowPackages.empty()) this->lastSequence = windowPackages.back().getSequence();

          if (windowPackages.size() == windowCount) {
            Package ack{Constants::INIT_MARKER, 0, this->lastSequence, PackageTypeEnum::ACK};
            this->rawSocket->sendPackage(ack);
          } else {
            uint8_t nackSequence = this->lastSequence + 1 <= 31 ? this->lastSequence + 1 : 0;
            Package nack{Constants::INIT_MARKER, 0, nackSequence, PackageTypeEnum::NACK};
            this->rawSocket->sendPackage(nack);
          }

          size_t range{windowPackages.size()};
          for (size_t i = 0; i < range; ++i) {
            if (!this->isDuplicated(packages, windowPackages.at(i))) {
              packages.push_back(windowPackages.at(i));
              ++recvPackages;
            }
          }
          windowPackages.clear();

          windowCount = 0;
          crcFailed = false;
          this->showProgress(recvPackages, totalPackages);
        }
      }
    }

    // wait for end trasmition
    running = true;
    while (running) {
      status = this->rawSocket->recvPackage(package);

      if (status == Constants::STATUS_OK) {
        if (package.checkCrc()) {
          if (package.getType() == PackageTypeEnum::END_TX) {
            Package ack{Constants::INIT_MARKER, 0, package.getSequence(), PackageTypeEnum::ACK};
            this->rawSocket->sendPackage(ack);

            std::cout << "\n" << std::endl;
            running = false;
          }
        } else {
          Package nack{Constants::INIT_MARKER, 0, this->lastSequence, PackageTypeEnum::NACK};
          this->rawSocket->sendPackage(nack);
        }
      }
    }

    // Writing file
    std::string path{std::string{Constants::DOWNLOADS_PATH} + "/" + this->videoName};
    std::vector<Package>::iterator it_package{packages.begin()};
    std::ofstream outFile(path);

    std::cout << "Salvando arquivo em " << path << std::endl;
    if (outFile) {
      while (it_package != packages.end()) {
        for (size_t i = 0; i < (*it_package).getDataSize(); ++i) outFile << (*it_package).getData()[i];
        ++it_package;
      }
    }
    outFile.close();

    // Opening video
    std::string command{"xdg-open " + path};
    if (system(command.c_str()) == -1) std::cout << "Impossibilitado de abrir o player padrao!\n" << std::endl;

    packages.clear();
  } catch (exceptions::TimeoutException& e) {
    std::cerr << "Connection Timeout - closing" << std::endl;
  }
}

bool ClientDownloadConnection::isDuplicated(const std::vector<Package>& packages, const Package& package) const {
  size_t startIndex = packages.size() > 5 ? packages.size() - 5 : 0;

  std::vector<Package>::const_iterator it_package{std::find_if(
      (packages.begin() + startIndex), packages.end(),
      [package](const Package& vec_package) { return vec_package.getSequence() == package.getSequence(); })};

  return it_package != packages.end();
}

void ClientDownloadConnection::showProgress(const uintmax_t recvPackages, const uintmax_t totalPackages) const {
  const int barWidth = 50;
  double progress = static_cast<double>(recvPackages) / totalPackages;

  std::cout << "[";
  int pos = barWidth * progress;
  for (int i = 0; i < barWidth; ++i) {
    if (i < pos)
      std::cout << "=";
    else if (i == pos)
      std::cout << ">";
    else
      std::cout << " ";
  }
  std::cout << "] " << int(progress * 100.0) << " % (" << recvPackages << "/" << totalPackages << ")\r";
}
}  // namespace network
