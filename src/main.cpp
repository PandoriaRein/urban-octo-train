#include "cmd_options.h"
#include "crypto_guard_ctx.h"
#include <fstream>
#include <iostream>
#include <print>
#include <stdexcept>
#include <string>

int main(int argc, char *argv[]) {
  try {

    CryptoGuard::ProgramOptions options;
    options.Parse(argc, argv);

    CryptoGuard::CryptoGuardCtx cryptoCtx;

    std::ifstream inStreamF(options.GetInputFile(), std::ios::binary);
    if (!inStreamF.good()) {
      throw std::runtime_error{"Input file was not found"};
    }

    std::ofstream outStreamF(options.GetOutputFile(), std::ios::binary);
    if (!outStreamF.good()) {
      throw std::runtime_error{"Output file was not found"};
    }
    std::string tmpStr;
    std::string tmpStr2;
    while (!inStreamF.eof()) {
      inStreamF >> tmpStr;
      if (tmpStr != "") {
        tmpStr2 += tmpStr + " ";
      }
    }
    tmpStr2.erase(tmpStr2.size() - 1);
    std::stringstream inputStream(tmpStr2);
    std::stringstream outputStream;

    using COMMAND_TYPE = CryptoGuard::ProgramOptions::COMMAND_TYPE;
    switch (options.GetCommand()) {
    case COMMAND_TYPE::ENCRYPT:
      cryptoCtx.EncryptFile(inputStream, outputStream, options.GetPassword());
      while (!outputStream.eof())
        outStreamF << outputStream.get();
      std::print("File encoded successfully\n");
      break;

    case COMMAND_TYPE::DECRYPT:
      cryptoCtx.DecryptFile(inputStream, outputStream, options.GetPassword());
      while (!outputStream.eof())
        outStreamF << outputStream.get();
      std::print("File decoded successfully\n");
      break;

    case COMMAND_TYPE::CHECKSUM:
      std::print("Checksum: {}\n", "CHECKSUM_NOT_IMPLEMENTED");
      break;

    default:
      throw std::runtime_error{"Unsupported command"};
    }

  } catch (const std::exception &e) {
    std::print(std::cerr, "Error: {}\n", e.what());
    return 1;
  }

  return 0;
}