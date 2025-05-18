#include "cmd_options.h"

#include <iostream>

namespace po = boost::program_options;

namespace CryptoGuard {

ProgramOptions::ProgramOptions() : desc_("Allowed options") {
  desc_.add_options()("help", "produce help message")(
      "command", po::value<std::string>(),
      "command")("i", po::value<std::string>(),
                 "input")("o", po::value<std::string>(),
                          "output")("p", po::value<std::string>(), "password");
}

ProgramOptions::~ProgramOptions() = default;

void ProgramOptions::Parse(int argc, char *argv[]) {
  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc_), vm);

  po::notify(vm);

  if (vm.count("help")) {
    std::cout << desc_ << "\n";
    return;
  }
  if (vm.count("i")) {
    std::cout << desc_ << "\n";
    return;
  }
}

} // namespace CryptoGuard
