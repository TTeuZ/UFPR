#include "SendRecvFailedException.hpp"

using namespace exceptions;

SendRecvFailedException::SendRecvFailedException(const std::string& desc)
    : runtime_error{"Fail in send package through socket"}, desc{desc} {};
