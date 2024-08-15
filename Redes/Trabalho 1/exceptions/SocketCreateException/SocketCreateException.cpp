#include "SocketCreateException.hpp"

using namespace exceptions;

SocketCreateException::SocketCreateException(const std::string& desc)
    : runtime_error{"Fail in create socket connection"}, desc{desc} {};
