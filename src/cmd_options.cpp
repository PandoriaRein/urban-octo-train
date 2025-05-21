#include "cmd_options.h"

#include <iostream>

namespace po = boost::program_options;

namespace CryptoGuard {

ProgramOptions::ProgramOptions() : desc_("Allowed options") {
  desc_.add_options()("help", "produce help message")(
      "i", po::value<std::vector<std::string>>(),
      "input")("o", po::value<std::vector<std::string>>(), "output")(
      "p", po::value<std::vector<std::string>>(),
      "password")("command", po::value<std::vector<std::string>>(), "command");
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
    std::vector<std::string> inputPath = vm["i"].as<std::vector<std::string>>();
    if (inputPath.size() > 0)
      inputFile_ = inputPath[0];
    else
      std::cout << "no input file"
                << "\n";
  }
  if (vm.count("o")) {
    std::vector<std::string> outputPath =
        vm["o"].as<std::vector<std::string>>();
    if (outputPath.size() > 0)
      outputFile_ = outputPath[0];
    else
      std::cout << "no output file"
                << "\n";
  }
  if (vm.count("p")) {
    std::vector<std::string> password = vm["p"].as<std::vector<std::string>>();
    if (password.size() > 0)
      password_ = password[0];
    else
      std::cout << "no password file"
                << "\n";
  }
  if (vm.count("command")) {
    std::vector<std::string> command =
        vm["command"].as<std::vector<std::string>>();
    if (command.size() > 0) {
      for (auto it = commandMapping_.begin(); it != commandMapping_.end();
           it++) {
        if (it->first == command[0])
          command_ = it->second;
      }
    } else
      std::cout << "no command"
                << "\n";
  }
}

} // namespace CryptoGuard
