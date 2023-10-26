#include "NaoPositivoException.hpp"

NaoPositivoException::NaoPositivoException(const std::string& desc)
    : std::invalid_argument{"Arqumento invalido"}, desc{desc} {}
