#include "NullPointerException.hpp"

using namespace ufpr;

NullPointerException::NullPointerException(const std::string& desc)
    : runtime_error{"O ponteiro não pode ser null"}, desc{desc} {};