#ifndef ARGPARSER_HPP
#define ARGPARSER_HPP

#include <boost/program_options.hpp>

namespace network {
class ArgParser {
 public:
  ArgParser() = delete;

  virtual ~ArgParser() = default;

  static bool parseArguments(int argc, char** argv);
};
}  // namespace network

#endif