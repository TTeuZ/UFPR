#include "ArgParser.hpp"

namespace po = boost::program_options;

namespace network {
bool ArgParser::parseArguments(int argc, char** argv) {
  bool loopback;

  po::options_description desc("Client/Server loopback");
  desc.add_options()("loopback", po::value<bool>(&loopback)->required(), "set loopback mode (true/false)");

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  return loopback;
}
}  // namespace network