#include "TimeoutException.hpp"

using namespace exceptions;

TimeoutException::TimeoutException(const std::string& desc)
    : runtime_error{"Timeout in connection"}, desc{desc} {};
