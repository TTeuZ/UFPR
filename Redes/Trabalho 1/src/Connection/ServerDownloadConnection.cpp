#include "ServerDownloadConnection.hpp"

namespace network {
ServerDownloadConnection::ServerDownloadConnection(RawSocket* rawSocket, const std::string& videoName)
    : Connection{rawSocket} {
  this->videoName = videoName;
};

void ServerDownloadConnection::run() {
  this->rawSocket->activeTimeout();
  Package package;
  int status;

  try {
    std::cout << "Iniciando conexao - DOWNLOAD - " << this->videoName << std::endl;

    Package ack{Constants::INIT_MARKER, 0, 0, PackageTypeEnum::ACK};
    this->rawSocket->sendPackage(ack);

    // Opening file
    std::string path{std::string{Constants::VIDEOS_PATH} + "/" + this->videoName};
    std::ifstream file{path, std::ios::binary};
    if (!file.is_open()) {
      std::cout << "Finalizando conexao - DOWNLOAD - " << this->videoName << std::endl;

      uint8_t errorCode[1] = {2};
      Package error{Constants::INIT_MARKER, 1, 1, PackageTypeEnum::ERROR, errorCode};
      this->rawSocket->sendPackage(error);
      this->wait_ack(error);

      this->rawSocket->deactiveTimeout();
      return;
    }

    // Creating header
    std::cout << "Enviando pacote de header" << std::endl;

    std::filesystem::path filePath(path);
    uintmax_t fileSize = std::filesystem::file_size(filePath);
    uint8_t fileSizeArray[sizeof(fileSize)];

    for (size_t i = 0; i < sizeof(fileSize); ++i)
      fileSizeArray[sizeof(fileSize) - 1 - i] = static_cast<uint8_t>((fileSize >> (i * 8)) & 0xFF);

    Package header{Constants::INIT_MARKER, sizeof(fileSize), 1, PackageTypeEnum::FILE_HEADER, fileSizeArray};
    this->rawSocket->sendPackage(header);
    this->wait_ack(header);

    // Create packages
    std::cout << "Coletando dados..." << std::endl;

    std::vector<Package> packages;
    uint8_t readBuffer[MAX_DATA_SIZE];
    int count{2};

    while (file) {
      file.read(reinterpret_cast<char*>(readBuffer), MAX_DATA_SIZE);
      std::streamsize bytesRead = file.gcount();

      if (bytesRead > 0)
        packages.push_back(Package{Constants::INIT_MARKER, static_cast<uint8_t>(bytesRead),
                                   static_cast<uint8_t>(count++ % Constants::MAX_SEQUENCE_SIZE), PackageTypeEnum::DATA,
                                   readBuffer});

      if (bytesRead < MAX_DATA_SIZE) break;
    }

    // Sending packages
    size_t windowCount{0};
    std::vector<uint8_t> sentSequences;
    std::vector<Package>::iterator it_package{packages.begin()};
    while (it_package != packages.end()) {
      std::cout << "Enviando pacote: " << (int)(*it_package).getSequence() << std::endl;

      sentSequences.push_back((*it_package).getSequence());
      this->rawSocket->sendPackage((*it_package++));
      ++windowCount;

      if ((windowCount % WINDOW_SIZE) == 0 || it_package == packages.end()) {
        status = this->rawSocket->recvPackage(package);

        if (status == Constants::STATUS_RETRY) {
          it_package -= sentSequences.size();
        } else if (package.getType() == PackageTypeEnum::NACK) {
          uint8_t nackSequence = package.getSequence();

          std::vector<uint8_t>::iterator it = std::find(sentSequences.begin(), sentSequences.end(), nackSequence);
          int indexOfFailed = std::distance(sentSequences.begin(), it);

          long failedQty = sentSequences.size() - indexOfFailed;
          it_package -= failedQty;
        }

        sentSequences.clear();
        windowCount = 0;
      }
    }

    // End transmissian
    Package end_tx{Constants::INIT_MARKER, 0, static_cast<uint8_t>(count % Constants::MAX_SEQUENCE_SIZE),
                   PackageTypeEnum::END_TX};
    this->rawSocket->sendPackage(end_tx);
    this->wait_ack(end_tx);

    std::cout << "Finalizando conexao - DOWNLOAD - " << this->videoName << std::endl << std::endl;

    file.close();
    packages.clear();
    this->rawSocket->deactiveTimeout();
  } catch (exceptions::TimeoutException& e) {
    this->rawSocket->deactiveTimeout();
    std::cerr << "Connection Timeout - closing" << std::endl;
  }
}
}  // namespace network
