#pragma once

#include <memory>
#include <openssl/evp.h>
#include <string>

namespace CryptoGuard {
class Impl;
class CryptoGuardCtx {
public:
  CryptoGuardCtx();
  ~CryptoGuardCtx();

  CryptoGuardCtx(const CryptoGuardCtx &) = delete;
  CryptoGuardCtx &operator=(const CryptoGuardCtx &) = delete;

  CryptoGuardCtx(CryptoGuardCtx &&) noexcept = default;
  CryptoGuardCtx &operator=(CryptoGuardCtx &&) noexcept = default;

  // API
  void EncryptFile(std::iostream &inStream, std::iostream &outStream,
                   std::string_view password);
  void DecryptFile(std::iostream &inStream, std::iostream &outStream,
                   std::string_view password);
  std::string CalculateChecksum(std::iostream &inStream);

private:
  std::unique_ptr<Impl> pImpl_;
};

} // namespace CryptoGuard
