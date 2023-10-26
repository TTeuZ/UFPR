#include "NullPointerException.hpp"

NullPointerException::NullPointerException(const std::string& desc)
    : runtime_error{"O ponteiro não pode ser null"}, desc{desc} {};