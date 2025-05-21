#include "crypto_guard_ctx.h"
#include <iostream>
#include <memory>
#include <print>
namespace CryptoGuard {
  void Impl::EncryptFile(std::iostream &inStream, std::iostream &outStream, std::string_view password){
    
    if (!inStream.good()||!outStream.good()) {
      std::print("Problem with streams.\n");
      return;
    }


        EVP_CipherUpdate(ctx, outBuf.data(), &outLen, inBuf.data(), static_cast<int>(16));
        for (int i = 0; i < outLen; ++i) {
            output.push_back(outBuf[i]);
        }

        // Обрабатываем оставшиеся символы
        EVP_CipherUpdate(ctx, outBuf.data(), &outLen, inBuf.data(), static_cast<int>(16));
        for (int i = 0; i < outLen; ++i) {
            output.push_back(outBuf[i]);
        }




  }
  void Impl::DecryptFile(std::iostream &inStream, std::iostream &outStream, std::string_view password){
    if (!inStream.good()||!outStream.good()) {
      std::print("Problem with streams.\n");
      return;
    }


  }
  std::string Impl::CalculateChecksum(std::iostream &inStream){

  }

struct AesCipherParams {
  static const size_t KEY_SIZE = 32;            // AES-256 key size
  static const size_t IV_SIZE = 16;             // AES block size (IV length)
  const EVP_CIPHER *cipher = EVP_aes_256_cbc(); // Cipher algorithm

  int encrypt;                             // 1 for encryption, 0 for decryption
  std::array<unsigned char, KEY_SIZE> key; // Encryption key
  std::array<unsigned char, IV_SIZE> iv;   // Initialization vector
};

AesCipherParams Impl::CreateChiperParamsFromPassword(std::string_view password){
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


Impl::Impl(){
  ctx = EVP_CIPHER_CTX_new();
  params = new AesCipherParams(CreateChiperParamsFromPassword("12341234"));
  params->encrypt = 1;
  OpenSSL_add_all_algorithms();
  EVP_CipherInit_ex(ctx, params->cipher, nullptr, params->key.data(),params->iv.data(), params->encrypt);
}
Impl::~Impl(){
     EVP_CIPHER_CTX_free(ctx);
     EVP_cleanup();


}



void CryptoGuardCtx::EncryptFile(std::iostream &inStream, std::iostream &outStream, std::string_view password) {
  pImpl_->EncryptFile(inStream,outStream,password);
  
  }
void CryptoGuardCtx::DecryptFile(std::iostream &inStream, std::iostream &outStream, std::string_view password) {
  pImpl_->DecryptFile(inStream,outStream,password);
}
std::string CryptoGuardCtx::CalculateChecksum(std::iostream &inStream) {
 return pImpl_->CalculateChecksum(inStream);
}

} // namespace CryptoGuard
