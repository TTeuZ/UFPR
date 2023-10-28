#include "NaoPositivoException.hpp"

using namespace ufpr::exceptions;

NaoPositivoException::NaoPositivoException(const std::string& desc)
    : std::invalid_argument{"Arqumento invalido"}, desc{desc} {}
