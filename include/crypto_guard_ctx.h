#pragma once

#include <string>
#include <string>
#include <openssl/evp.h>
#include <memory>

namespace CryptoGuard {
struct AesCipherParams;
 class Impl {
  public:
    Impl();

    ~Impl();

    AesCipherParams CreateChiperParamsFromPassword(std::string_view password);

  void EncryptFile(std::iostream &inStream, std::iostream &outStream,
                   std::string_view password);
  void DecryptFile(std::iostream &inStream, std::iostream &outStream,
                   std::string_view password);
  std::string CalculateChecksum(std::iostream &inStream);
  private:
  EVP_CIPHER_CTX *ctx;
  AesCipherParams* params;
 };

class CryptoGuardCtx {
public:
  CryptoGuardCtx() {}
  ~CryptoGuardCtx() {}

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
