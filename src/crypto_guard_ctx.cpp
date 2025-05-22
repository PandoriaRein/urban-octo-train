#include "crypto_guard_ctx.h"
#include <iostream>
#include <memory>
#include <print>
#include <string>
#include <vector>

namespace CryptoGuard {
struct AesCipherParams {
  static const size_t KEY_SIZE = 32;            // AES-256 key size
  static const size_t IV_SIZE = 32;             // AES block size (IV length)
  const EVP_CIPHER *cipher = EVP_aes_256_cbc(); // Cipher algorithm

  int encrypt;                             // 1 for encryption, 0 for decryption
  std::array<unsigned char, KEY_SIZE> key; // Encryption key
  std::array<unsigned char, IV_SIZE> iv;   // Initialization vector
};

class Impl {

public:
  Impl() {
    OpenSSL_add_all_algorithms();
    ctx = EVP_CIPHER_CTX_new();
  }

  ~Impl() {
    EVP_CIPHER_CTX_free(ctx);
    EVP_cleanup();
  }

  AesCipherParams CreateChiperParamsFromPassword(std::string_view password) {
    AesCipherParams params;
    constexpr std::array<unsigned char, 8> salt = {'1', '2', '3', '4',
                                                   '5', '6', '7', '8'};

    int result =
        EVP_BytesToKey(params.cipher, EVP_sha256(), salt.data(),
                       reinterpret_cast<const unsigned char *>(password.data()),
                       password.size(), 1, params.key.data(), params.iv.data());

    if (result == 0) {
      throw std::runtime_error{"Failed to create a key from password"};
    }

    return params;
  }

  void EncryptFile(std::iostream &inStream, std::iostream &outStream,
                   std::string_view password) {
    if (!inStream.good() || !outStream.good()) {
      std::print("Problem with streams.\n");
      return;
    }
    params = new AesCipherParams(CreateChiperParamsFromPassword(password));
    params->encrypt = 1;
    Cipher(inStream, outStream);
    return;
  }

  void Cipher(std::iostream &inStream, std::iostream &outStream) {
    EVP_CipherInit_ex(ctx, params->cipher, nullptr, params->key.data(),
                      params->iv.data(), params->encrypt);
    while (!inStream.eof()) {
      std::string tmpIn;
      inStream >> tmpIn;
      std::vector<unsigned char> inBuf(tmpIn.begin(), tmpIn.end());
      std::vector<unsigned char> outBuf(inBuf.size());
      int outLen = outBuf.size();
      if (!inStream.good() || !outStream.good()) {
        if (inStream.eof() || outStream.eof()) {
          EVP_CipherFinal_ex(ctx, outBuf.data(), &outLen);
          outStream << outBuf.data();
          return;
        } else {
          throw std::runtime_error{"Problem with streams.\n"};
          return;
        }
      }
      EVP_CipherUpdate(ctx, outBuf.data(), &outLen, inBuf.data(),
                       static_cast<int>(inBuf.size()));
      outStream << outBuf.data();
    }
  }

  void DecryptFile(std::iostream &inStream, std::iostream &outStream,
                   std::string_view password) {
    if (!inStream.good() || !outStream.good()) {
      std::print("Problem with streams.\n");
      return;
    }
    params = new AesCipherParams(CreateChiperParamsFromPassword(password));
    Cipher(inStream, outStream);
  }

  std::string CalculateChecksum(std::iostream &inStream) {
    if (!inStream.good()) {
      std::print("Problem with stream.\n");
      return "";
    }
  }

private:
  EVP_CIPHER_CTX *ctx;
  AesCipherParams *params;
};

void CryptoGuardCtx::EncryptFile(std::iostream &inStream,
                                 std::iostream &outStream,
                                 std::string_view password) {
  pImpl_->EncryptFile(inStream, outStream, password);
}

void CryptoGuardCtx::DecryptFile(std::iostream &inStream,
                                 std::iostream &outStream,
                                 std::string_view password) {
  pImpl_->DecryptFile(inStream, outStream, password);
}

std::string CryptoGuardCtx::CalculateChecksum(std::iostream &inStream) {
  return pImpl_->CalculateChecksum(inStream);
}
CryptoGuardCtx::CryptoGuardCtx() : pImpl_() {
  pImpl_ = std::make_unique<Impl>();
}
CryptoGuardCtx::~CryptoGuardCtx() {}
} // namespace CryptoGuard
