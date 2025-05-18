#include "crypto_guard_ctx.h"
namespace CryptoGuard {

void CryptoGuardCtx::EncryptFile(std::iostream &inStream,
                                 std::iostream &outStream,
                                 std::string_view password) {}
void CryptoGuardCtx::DecryptFile(std::iostream &inStream,
                                 std::iostream &outStream,
                                 std::string_view password) {}
std::string CryptoGuardCtx::CalculateChecksum(std::iostream &inStream) {
  return "NOT_IMPLEMENTED";
}

} // namespace CryptoGuard
